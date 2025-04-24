///////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

///////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////

template < typename T, typename C = std::deque < T > > class Queue
{
public :

    using mutex_t = std::mutex;

//  -----------------------------------------------------------------------

    Queue() = default;

//  -----------------------------------------------------------------------

    Queue(Queue const & other)
    {
        std::scoped_lock < std::mutex > lock(other.m_mutex);

        m_container = other.m_container;
    }

//  -----------------------------------------------------------------------

    Queue(Queue && other)
    {
        std::scoped_lock < std::mutex > lock(other.m_mutex);

        m_container = std::move(other.m_container);
    }

//  -----------------------------------------------------------------------

    auto & operator=(Queue const & other)
    {
        std::scoped_lock < mutex_t, mutex_t > lock(m_mutex, other.m_mutex);

        m_container = other.m_container;

        return *this;
    }

//  -----------------------------------------------------------------------

    auto & operator=(Queue && other)
    {
        std::scoped_lock < mutex_t, mutex_t > lock(m_mutex, other.m_mutex);

        m_container = std::move(other.m_container);

        return *this;
    }

//  -----------------------------------------------------------------------

    void push(T x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        m_container.push_back(x);

        m_condition.notify_one();
    }

//  -----------------------------------------------------------------------

    auto wait_and_pop()
    {
        std::unique_lock < std::mutex > lock(m_mutex);

        while (std::empty(m_container))
        {
            m_condition.wait(lock);
        }

        auto x = std::make_shared < T > (m_container.front());

        m_container.pop_front();

        return x;
    }

//  -----------------------------------------------------------------------

    void wait_and_pop(T & x)
    {
        std::unique_lock < std::mutex > lock(m_mutex);

        while (std::empty(m_container))
        {
            m_condition.wait(lock);
        }

        x = m_container.front();

        m_container.pop_front();
    }

//  -----------------------------------------------------------------------

    auto try_pop() -> std::shared_ptr < T >
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        if(!std::empty(m_container))
        {
            auto x = std::make_shared < T > (m_container.front());

            m_container.pop_front();

            return x;
        }
        
        return nullptr;
    }

//  -----------------------------------------------------------------------

    auto try_pop(T & x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        if(!std::empty(m_container))
        {
            x = m_container.front();

            m_container.pop_front();

            return true;
        }
        
        return false;
    }

private :

    C m_container;

//  -----------------------------------------------------------------------

    mutable std::mutex m_mutex;

    mutable std::condition_variable m_condition;
};

///////////////////////////////////////////////////////////////////////////

void produce(Queue < int > & queue)
{
    std::this_thread::sleep_for(1s);

    for (auto i = 0; i < 1'000; ++i)
    {
        queue.push(i + 1);
    }
}

///////////////////////////////////////////////////////////////////////////

void consume(Queue < int > & queue)
{
    for (auto i = 0; i < 1'000; ++i)
    {
        assert(*queue.wait_and_pop() == i + 1);
    }
}

///////////////////////////////////////////////////////////////////////////

int main()
{
    Queue < int > queue;

//  ------------------------------------------------

    std::jthread thread_1(produce, std::ref(queue));

    std::jthread thread_2(consume, std::ref(queue));
}

///////////////////////////////////////////////////////////////////////////