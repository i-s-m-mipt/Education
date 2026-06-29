//////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

//////////////////////////////////////////////////////////////////////////////////////////////////

// content : Thread Pools
//
// content : Metafunction std::result_of

//////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <atomic>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <deque>
#include <format>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <syncstream>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////

class Pool
{
private :

    class Task : private boost::noncopyable
    {
    private :

        class Callable_Base
        {
        public :

            virtual ~Callable_Base() = default;

        //  -----------------------------------

            virtual void call() = 0;
        };

    //  ------------------------------------------------------------------------------------------

        template < typename F > class Callable : public Callable_Base
        {
        public :

            Callable(F && f) : m_f(std::forward < F > (f)) {}

        //  -------------------------------------------------

            void call() override
            {
                m_f();
            }

        private :

            F m_f;
        };

    public :

        Task() = default;

    //  ------------------------------------------------------------------------------------------

        template
        <
            typename F
        >
        Task(F && f) : m_callable(std::make_unique < Callable < F > > (std::forward < F > (f))) {}

    //  ------------------------------------------------------------------------------------------

        Task(Task && other) : m_callable(std::move(other.m_callable)) {}

    //  ------------------------------------------------------------------------------------------

        auto & operator=(Task && other)
        {
            m_callable = std::move(other.m_callable);

            return *this;
        }

    //  ------------------------------------------------------------------------------------------

        void operator()() const
        {
            m_callable->call();
        }

    private :

        std::unique_ptr < Callable_Base > m_callable;
    };

//  ----------------------------------------------------------------------------------------------

    template < typename T, typename C = std::deque < T > > class Queue
    {
    public :

        void push(T && x)
        {
            std::scoped_lock < std::mutex > lock(m_mutex);

            m_container.push_back(std::move(x));
        }

    //  --------------------------------------------------

        auto top_and_pop(T & x)
        {
            std::scoped_lock < std::mutex > lock(m_mutex);

            if (!std::empty(m_container))
            {
                x = std::move(m_container.front());

                m_container.pop_front();

                return true;
            }

            return false;
        }

    private :

        C m_container;

    //  --------------------------------------------------

        mutable std::mutex m_mutex;
    };

public :

    Pool()
    {
        for (auto i = 0uz; i < std::thread::hardware_concurrency(); ++i)
        {
            m_threads.emplace_back(std::jthread(&Pool::run, this));
        }
    }

//  ----------------------------------------------------------------------------------------------

   ~Pool()
    {
        m_flag = true;
    }

//  ----------------------------------------------------------------------------------------------

    template < typename F > auto post(F && f)
    {
        std::packaged_task < std::result_of_t < F() > () > task(std::move(f));

        auto future = task.get_future();

        m_tasks.push(std::move(task));

        return future;
    }

private :

    void run()
    {
        Task task;

        while (!m_flag)
        {
            if (m_tasks.top_and_pop(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }

//  ----------------------------------------------------------------------------------------------

    std::vector < std::jthread > m_threads;

    Queue < Task > m_tasks;

    std::atomic < bool > m_flag = false;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

auto calculate(std::size_t size)
{
    auto id = std::this_thread::get_id();

    std::osyncstream(std::cout) << std::format("calculate : id = {}\n", id);

	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(x), 2) + std::pow(std::cos(x), 2);
	}

	return x;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Pool pool;

//  --------------------------------------------------------

    std::vector < std::future < double > > futures(1 << 10);

//  --------------------------------------------------------

    for (auto & future : futures)
    {
        auto lambda = [](){ return calculate(1 << 10); };

    //  -------------------------------------------------

        future = pool.post(std::move(lambda));
    }

//  --------------------------------------------------------

    for (auto & future : futures)
    {
        assert(equal(future.get(), 1 << 10));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////