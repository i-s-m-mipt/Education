/////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

/////////////////////////////////////////////////////////////////////////////////

// section : Synchronization

/////////////////////////////////////////////////////////////////////////////////

// content : Thread-Safe Queues

/////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

/////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////////////////////////////////////////////

template < typename T, typename C = std::deque < T > > class Queue
{
public :

    Queue() = default;

//  -----------------------------------------------------------------------------

    Queue(Queue const & other)
    {
        std::scoped_lock < std::mutex > lock(other.m_mutex);

        m_container = other.m_container;
    }

//  -----------------------------------------------------------------------------

    Queue(Queue && other) : Queue()
    {
        swap(other);
    }

//  -----------------------------------------------------------------------------

    auto & operator=(Queue other)
	{
        swap(other);

		return *this;
	}

//  -----------------------------------------------------------------------------

    void swap(Queue & other)
    {
        std::scoped_lock < std::mutex, std::mutex > lock(m_mutex, other.m_mutex);

        std::swap(m_container, other.m_container);
    }

//  -----------------------------------------------------------------------------

    void push(T x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        m_container.push_back(x);

        m_condition.notify_one();
    }

//  -----------------------------------------------------------------------------

    auto top_and_pop_v1()
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

//  -----------------------------------------------------------------------------

    void top_and_pop_v2(T & x)
    {
        std::unique_lock < std::mutex > lock(m_mutex);

        while (std::empty(m_container))
        {
            m_condition.wait(lock);
        }

        x = m_container.front();

        m_container.pop_front();
    }

//  -----------------------------------------------------------------------------

    auto top_and_pop_v3() -> std::shared_ptr < T >
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        if (!std::empty(m_container))
        {
            auto x = std::make_shared < T > (m_container.front());

            m_container.pop_front();

            return x;
        }

        return nullptr;
    }

//  -----------------------------------------------------------------------------

    auto top_and_pop_v4(T & x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        if (!std::empty(m_container))
        {
            x = m_container.front();

            m_container.pop_front();

            return true;
        }

        return false;
    }

private :

    C m_container;

//  -----------------------------------------------------------------------------

    mutable std::mutex m_mutex;

    mutable std::condition_variable m_condition;
};

/////////////////////////////////////////////////////////////////////////////////

void produce(Queue < int > & queue)
{
    std::this_thread::sleep_for(1s);

    for (auto i = 1; i < (1 << 10) + 1; ++i)
    {
        queue.push(i);
    }
}

/////////////////////////////////////////////////////////////////////////////////

void consume(Queue < int > & queue)
{
    for (auto i = 1; i < (1 << 10) + 1; ++i)
    {
        assert(*queue.top_and_pop_v1() == i);
    }
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    Queue < int > queue_1;

	Queue < int > queue_2 = queue_1;

	Queue < int > queue_3 = std::move(queue_2);

//  --------------------------------------------------

	queue_2 = queue_1;

	queue_3 = std::move(queue_2);

//  --------------------------------------------------

    std::jthread thread_1(produce, std::ref(queue_1));

    std::jthread thread_2(consume, std::ref(queue_1));
}

/////////////////////////////////////////////////////////////////////////////////