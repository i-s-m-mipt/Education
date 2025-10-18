//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////////////////////////

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
    auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

    std::vector < std::future < double > > futures(concurrency);

    std::shared_ptr < Task > task;
    
    if (state.range(0) == 0) { task = std::make_shared < Task_v1 > (); }

    if (state.range(0) == 1) { task = std::make_shared < Task_v2 > (); }

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

BENCHMARK(test)->Arg(0)->Arg(1);

//////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////////////////////////////////////