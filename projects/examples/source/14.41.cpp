////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <atomic>
#include <barrier>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <ranges>
#include <thread>
#include <tuple>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

#include <boost/lockfree/stack.hpp>
#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////////

#include "08.35.hpp"

////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Stack_v1 : private boost::noncopyable
{
public :

    Stack_v1(std::size_t capacity)
    {
        m_vector.reserve(capacity);
    }

//  --------------------------------------------------

    void push(T x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        m_vector.push_back(x);
    }

//  --------------------------------------------------

    void top_and_pop(T & x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        x = m_vector.back();

        m_vector.pop_back();
    }

private :

    std::vector < T > m_vector;

//  --------------------------------------------------

    mutable std::mutex m_mutex;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Stack_v2 : private boost::noncopyable
{
private :

    struct Node
    {
        std::shared_ptr < T > x;

        Node * next = nullptr;
    };

public :

   ~Stack_v2()
    {
        while (top_and_pop());
    }

//  ----------------------------------------------------------------------

    void push(T x)
    {
        auto node = new Node(std::make_shared < T > (x), nullptr);

        node->next = m_head.load(std::memory_order::relaxed);

        while
        (
            !m_head.compare_exchange_weak
            (
                node->next, node, 

                std::memory_order::release, 

                std::memory_order::relaxed
            )
        );
    }

//  ----------------------------------------------------------------------

    auto top_and_pop()
    {
        m_counter.fetch_add(1, std::memory_order::relaxed);

        auto head = m_head.load(std::memory_order::relaxed);

        while 
        (
            head && !m_head.compare_exchange_weak
            (
                head, head->next,

                std::memory_order::acquire,

                std::memory_order::relaxed
            )
        );

        std::shared_ptr < T > x;

        if (head)
        {
            x.swap(head->x);
        }

        try_clear(head);

        return x;
    }

private :

    void try_clear(Node * head)
    {
        if (m_counter.load(std::memory_order::relaxed) == 1)
        {
            auto tail = m_tail.exchange(nullptr);

            if (!(m_counter.fetch_sub(1, std::memory_order::relaxed) - 1))
            {
                clear(tail);
            }
            else if (tail)
            {
                save_nodes(tail);
            }

            delete head;
        }
        else
        {
            save_node(head);

            m_counter.fetch_sub(1, std::memory_order::relaxed);
        }
    }

//  ----------------------------------------------------------------------

    void clear(Node * nodes) const
    {
        while (nodes)
        {
            auto next = nodes->next;

            delete nodes;

            nodes = next;
        }
    }

//  ----------------------------------------------------------------------

    void save_nodes(Node * nodes)
    {
        auto end = nodes;

        while(auto next = end->next)
        {
            end = next;
        }

        save_nodes(nodes, end);
    }

//  ----------------------------------------------------------------------

    void save_nodes(Node * begin, Node * end)
    {
        end->next = m_tail;

        while (!m_tail.compare_exchange_weak(end->next, begin));
    }

//  ----------------------------------------------------------------------

    void save_node(Node * node)
    {
        save_nodes(node, node);
    }

//  ----------------------------------------------------------------------

    std::atomic < Node * > m_head = nullptr, m_tail = nullptr;

    std::atomic < std::size_t > m_counter = 0;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Stack_v3 : private boost::noncopyable
{
private :

    struct Node
    {
        std::shared_ptr < T > x;

        std::atomic < std::shared_ptr < Node > > next;
    };

public :

   ~Stack_v3()
    {
        while (top_and_pop());
    }

//  --------------------------------------------------------------------------------

    void push(T x)
    {
        auto node = std::make_shared < Node > (std::make_shared < T > (x), nullptr);

        auto expected = m_head.load(std::memory_order::relaxed);

        do
        {
            node->next = expected;
        }
        while
        (
            !m_head.compare_exchange_weak
            (
                expected, node, 

                std::memory_order::release,

                std::memory_order::relaxed
            )
        );
    }

//  --------------------------------------------------------------------------------

    auto top_and_pop()
    {
        auto head = m_head.load(std::memory_order::relaxed);

        while 
        (
            head && !m_head.compare_exchange_weak
            (
                head, head->next.load(std::memory_order::relaxed),

                std::memory_order::acquire,

                std::memory_order::relaxed
            )
        );

        if (head)
        {
            head->next = std::shared_ptr < Node > ();

            return head->x;
        }

        return std::shared_ptr < T > ();
    }

private :

    std::atomic < std::shared_ptr < Node > > m_head = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename T > using Stack_v4 = boost::lockfree::stack < T > ;

////////////////////////////////////////////////////////////////////////////////////

class Task
{
public :

    virtual ~Task() = default;

//  ------------------------------------------

    auto operator()(std::barrier <> & barrier)
    {
        barrier.arrive_and_wait();

        Timer timer;

        test();

        return timer.elapsed().count();
    }

//  ------------------------------------------

    virtual void test() = 0;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename S > class Task_v1 : public Task
{
public :

    Task_v1(S & stack) : m_stack(stack) {}

//  ----------------------------------------

    void test() override
    {
        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            m_stack.push(i + 1);
        }
    }

private :

    S & m_stack;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename S > class Task_v2 : public Task
{
public :

    Task_v2(S & stack) : m_stack(stack) {}

//  ----------------------------------------

    void test() override
    {
        auto x = 0;

        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            m_stack.top_and_pop(x);
        }
    }

private :

    S & m_stack;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename S > class Task_v3 : public Task
{
public :

    Task_v3(S & stack) : m_stack(stack) {}

//  --------------------------------------------

    void test() override
    {
        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            std::ignore = m_stack.top_and_pop();
        }
    }

private :

    S & m_stack;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename S > class Task_v4 : public Task
{
public :

    Task_v4(S & stack) : m_stack(stack) {}

//  ----------------------------------------

    void test() override
    {
        auto x = 0;

        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            m_stack.pop(x);
        }
    }

private :

    S & m_stack;
};

////////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto argument = state.range(0);

    auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

    std::vector < std::future < double > > futures(concurrency);

    auto size = concurrency * (1 << 10);

    Stack_v1 < int > stack_v1(2 * size);

    Stack_v2 < int > stack_v2;

    Stack_v3 < int > stack_v3;

    Stack_v4 < int > stack_v4(2 * size);

    for (auto i = 0uz; i < size; ++i)
    {
        stack_v1.push(i + 1);

        stack_v2.push(i + 1);

        stack_v3.push(i + 1);

        stack_v4.push(i + 1);
    }

    std::shared_ptr < Task > task_1;

    std::shared_ptr < Task > task_2;

    switch (argument)
    {
        case 1 :
        {
            task_1 = std::make_shared < Task_v1 < Stack_v1 < int > > > (stack_v1);

            task_2 = std::make_shared < Task_v2 < Stack_v1 < int > > > (stack_v1);

            break;
        }

        case 2 :
        {
            task_1 = std::make_shared < Task_v1 < Stack_v2 < int > > > (stack_v2);

            task_2 = std::make_shared < Task_v3 < Stack_v2 < int > > > (stack_v2);

            break;
        }

        case 3 :
        {
            task_1 = std::make_shared < Task_v1 < Stack_v3 < int > > > (stack_v3);

            task_2 = std::make_shared < Task_v3 < Stack_v3 < int > > > (stack_v3);

            break;
        }

        case 4 :
        {
            task_1 = std::make_shared < Task_v1 < Stack_v4 < int > > > (stack_v4);

            task_2 = std::make_shared < Task_v4 < Stack_v4 < int > > > (stack_v4);

            break;
        }
    }

    std::barrier <> barrier(concurrency + 1);

    auto lambda = [](auto & future){ return future.get(); };

    for (auto element : state)
    {
        for (auto i = 0uz; i < concurrency / 2; ++i)
        {
            futures[i] = std::async
            (
                std::launch::async, &Task::operator(), task_1, std::ref(barrier)
            );
        }

        for (auto i = concurrency / 2; i < concurrency; ++i)
        {
            futures[i] = std::async
            (
                std::launch::async, &Task::operator(), task_2, std::ref(barrier)
            );
        }

        barrier.arrive_and_wait();

        auto time = *std::ranges::fold_left_first
        (
            std::views::transform(futures, lambda), std::plus()
        );

        state.SetIterationTime(time / concurrency);

		benchmark::DoNotOptimize(*task_1);

        benchmark::DoNotOptimize(*task_2);
    }
}

////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2)->Arg(3)->Arg(4);

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////////////////////////////////////////////////