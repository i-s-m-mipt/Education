/////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

/////////////////////////////////////////////////////////////////////////////////////////

// content : Cache Coherence Protocols
//
// content : Modified, Exclusive, Shared and Invalid Cache Line States
//
// content : False Sharing
//
// content : Object std::hardware_destructive_interference_size
//
// content : Microbenchmarking

/////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <atomic>
#include <barrier>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <new>
#include <ranges>
#include <thread>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

/////////////////////////////////////////////////////////////////////////////////////////

#include "08.34.hpp"

/////////////////////////////////////////////////////////////////////////////////////////

struct Entity_v1
{
    std::atomic < int > x = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////

struct alignas(std::hardware_destructive_interference_size) Entity_v2
{
    std::atomic < int > x = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////

class Task_Base
{
public :

    virtual ~Task_Base() = default;

//  -------------------------------------------------------------

    auto operator()(std::barrier <> & barrier, std::size_t index)
    {
        barrier.arrive_and_wait();

        Timer timer;

        test(index);

        return timer.elapsed().count();
    }

//  -------------------------------------------------------------

    virtual void test(std::size_t index) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////

template < typename E > class Task : public Task_Base
{
public :

    Task(std::size_t size) : m_entities(size) {}

//  --------------------------------------------

    void test(std::size_t index) override
    {
        for (auto i = 0uz; i < 1 << 20; ++i)
        {
            m_entities.at(index).x = 1;
        }
    }

private :

    std::vector < E > m_entities;
};

/////////////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto argument = state.range(0);

    auto concurrency = std::thread::hardware_concurrency();

    std::vector < std::future < double > > futures(concurrency);

    std::shared_ptr < Task_Base > task;

    switch (argument)
    {
        case 1 : { task = std::make_shared < Task < Entity_v1 > > (concurrency); break; }

        case 2 : { task = std::make_shared < Task < Entity_v2 > > (concurrency); break; }
    }

    std::barrier <> barrier(concurrency + 1);

    auto lambda = [](auto & future) static { return future.get(); };

    for (auto element : state)
    {
        for (auto i = 0uz; i < concurrency; ++i)
        {
            futures[i] = std::async
            (
                std::launch::async, &Task_Base::operator(), task, std::ref(barrier), i
            );
        }

        barrier.arrive_and_wait();

        auto time = *std::ranges::fold_left_first
        (
            std::views::transform(futures, lambda), std::plus()
        );

        state.SetIterationTime(time / concurrency);

		benchmark::DoNotOptimize(*task);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2);

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

/////////////////////////////////////////////////////////////////////////////////////////