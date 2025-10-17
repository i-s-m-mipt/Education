///////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <atomic>
#include <barrier>
#include <chrono>
#include <functional>
#include <future>
#include <memory>
#include <ranges>
#include <thread>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////

template < typename D = std::chrono::duration < double > > class Timer
{
public :

	Timer() : m_begin(clock_t::now()) {}

//  -----------------------------------------------------------------------

	auto elapsed() const
	{
		return std::chrono::duration_cast < D > (clock_t::now() - m_begin);
	}

private :

    using clock_t = std::chrono::steady_clock;

//  -----------------------------------------------------------------------
	
	clock_t::time_point m_begin;
};

///////////////////////////////////////////////////////////////////////////////////////////

class Task
{
public :

    auto operator()(std::barrier <> & barrier, std::atomic < int > & x) const
    {
        barrier.arrive_and_wait();

        Timer timer;

        test(x);

        return timer.elapsed().count();
    }

private :

    virtual void test(std::atomic < int > & x) const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////

class Task_v1 : public Task
{
private :

    void test(std::atomic < int > & x) const override
    {
        for (auto i = 0uz; i < 1'000'000; ++i)
        {
            x.store(1, std::memory_order::seq_cst);
        }
    }
};

///////////////////////////////////////////////////////////////////////////////////////////

class Task_v2 : public Task
{
private :

    void test(std::atomic < int > & x) const override
    {
        for (auto i = 0uz; i < 1'000'000; ++i)
        {
            x.store(1, std::memory_order::relaxed);
        }
    }
};

///////////////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

    std::vector < std::future < double > > futures(concurrency);

    std::shared_ptr < Task > task;
    
    if (state.range(0) == 0) { task = std::make_shared < Task_v1 > (); }

    if (state.range(0) == 1) { task = std::make_shared < Task_v2 > (); }

    std::barrier <> barrier(concurrency + 1);

    std::atomic < int > x = 1;

    auto lambda = [](auto & future){ return future.get(); };

    for (auto element : state)
    {
        for (auto & future : futures)
        {
            future = std::async
            (
                std::launch::async, &Task::operator(), task, std::ref(barrier), std::ref(x)
            );
        }

        barrier.arrive_and_wait();

        auto time = *std::ranges::fold_left_first
        (
            std::ranges::views::transform(futures, lambda), std::plus()
        );

        state.SetIterationTime(time / concurrency);

		benchmark::DoNotOptimize(x);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(0)->Arg(1);

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////////////