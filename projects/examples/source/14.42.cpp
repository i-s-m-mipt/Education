//////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <barrier>
#include <functional>
#include <future>
#include <memory>
#include <new>
#include <ranges>
#include <thread>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////////////////////////

#include "08.35.hpp"

//////////////////////////////////////////////////////////////////////////////

class Task
{
public :

    auto operator()(std::barrier <> & barrier)
    {
        auto kb = 1uz << 10;

        std::vector < void * > vector(kb, nullptr);

        barrier.arrive_and_wait();

        Timer timer;

		for (auto i = 0uz; i < kb; ++i)
		{
			vector[i] = operator new(kb);
		}

		for (auto i = 0uz; i < kb; ++i)
		{
			operator delete(vector[i], kb);
		}

        return timer.elapsed().count();
    }
};

//////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

    std::vector < std::future < double > > futures(concurrency);

    auto task = std::make_shared < Task > ();

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

BENCHMARK(test);

//////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////////////////////////////////////