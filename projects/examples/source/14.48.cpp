//////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

//////////////////////////////////////////////////////////////////////////////////

// content : Lock-Free Stacks
//
// content : Library Boost.Lockfree
//
// content : Microbenchmarking

//////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <barrier>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <ranges>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////

#include <boost/lockfree/stack.hpp>

//////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////////////////////////////

#include "08.36.hpp"

//////////////////////////////////////////////////////////////////////////////////

template < typename T, typename C = std::vector < T > > class Stack_v1
{
public :

    void push(T x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        m_container.push_back(x);
    }

//  --------------------------------------------------

    auto top_and_pop(T & x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        if (!std::empty(m_container))
        {
            x = m_container.back();

            m_container.pop_back();

            return true;
        }
        else
        {
            return false;
        }
    }

private :

    C m_container;

//  --------------------------------------------------

    mutable std::mutex m_mutex;
};

//////////////////////////////////////////////////////////////////////////////////

template < typename T > using Stack_v2 = boost::lockfree::stack < T > ;

//////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////

template < typename S > class Task_v1 : public Task
{
public :

    Task_v1(S & stack) : m_stack(stack) {}

//  --------------------------------------------

    void test() override
    {
        for (auto i = 1; i < (1 << 10) + 1; ++i)
        {
            m_stack.push(i);
        }
    }

private :

    S & m_stack;
};

//////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////

template < typename S > class Task_v3 : public Task
{
public :

    Task_v3(S & stack) : m_stack(stack) {}

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

//////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto argument = state.range(0);

    auto concurrency = 2uz;

    std::vector < std::future < double > > futures(concurrency);

    auto size = concurrency * (1 << 10);

    Stack_v1 < int > stack_v1;

    Stack_v2 < int > stack_v2(2 * size);

    for (auto i = 1; i < static_cast < int > (size) + 1; ++i)
    {
        stack_v1.push(i);

        stack_v2.push(i);
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

//////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2);

//////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////////////////////////////////////////