//////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <atomic>
#include <barrier>
#include <functional>
#include <future>
#include <memory>
#include <ranges>
#include <thread>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////////////////////////

#include "08.39.hpp"

//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////

class Task_v1 : public Task
{
public :

    void test() override
    {
        for (auto i = 0uz; i < 1'000'000; ++i)
        {
            m_x.store(1, std::memory_order::seq_cst);
        }
    }

private :

    std::atomic < int > m_x = 0;
};

//////////////////////////////////////////////////////////////////////////////

class Task_v2 : public Task
{
public :

    void test() override
    {
        for (auto i = 0uz; i < 1'000'000; ++i)
        {
            m_x.store(1, std::memory_order::relaxed);
        }
    }

private :

    std::atomic < int > m_x = 0;
};

//////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto argument = state.range(0);

    auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

    std::vector < std::future < double > > futures(concurrency);

    std::shared_ptr < Task > task;

    switch (argument)
    {
        case 1 : { task = std::make_shared < Task_v1 > (); break; }

        case 2 : { task = std::make_shared < Task_v2 > (); break; }
    }

    std::barrier <> barrier(concurrency + 1);

    auto lambda = [](auto & future){ return future.get(); };

    for (auto element : state)
    {
        for (auto & future : futures)
        {
            future = std::async
            (
                std::launch::async, &Task::operator(), task, std::ref(barrier)
            );
        }

        barrier.arrive_and_wait();

        auto time = *std::ranges::fold_left_first
        (
            std::ranges::views::transform(futures, lambda), std::plus()
        );

        state.SetIterationTime(time / concurrency);

		benchmark::DoNotOptimize(*task);
    }
}

//////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2);

//////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////////////////////////////////////