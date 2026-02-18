////////////////////////////////////////////////////////////////////////////////

// chapter : Debugging and Profiling

////////////////////////////////////////////////////////////////////////////////

// section : Software Analysis Tools

////////////////////////////////////////////////////////////////////////////////

// content : Microbenchmarking
//
// content : Library Google.Benchmark
//
// content : Disabling CPU Frequency Scaling
//
// content : Disabling Address Space Layout Randomization
//
// content : Setting Task Affinity
//
// content : Setting Task Scheduling Algorithm
//
// content : Preemptive and Cooperative Multitasking
//
// content : Round Robin and FIFO Algorithms
//
// content : Tools cpupower, setarch, taskset and chrt
//
// content : Algorithms std::ranges::iota and std::ranges::lower_bound

////////////////////////////////////////////////////////////////////////////////

// support : sudo cpupower frequency-set -d 5.0GHz -u 5.0GHz
//
// support : sudo setarch $(uname -m) -R taskset -c 0 chrt -f 99 ./07.23

////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cmath>
#include <exception>
#include <numeric>
#include <stdexcept>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state) 
{
    for (auto element : state)
    {
        auto x = 0.0;

		for (auto i = 0uz; i < 1'000; ++i)
		{
			x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
		}

        benchmark::DoNotOptimize(x);
    }
}

////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    for (auto element : state)
    {
        auto x = 0.0;

        try
        {
            for (auto i = 0uz; true; ++i)
            {
                x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);

                if (i >= 1'000) 
                {
                    throw std::runtime_error("error");
                }
            }
        }
        catch (...) {}

        benchmark::DoNotOptimize(x);
    }
}

////////////////////////////////////////////////////////////////////////////////

void test_v3(benchmark::State & state) 
{
    for (auto element : state) 
    {
        std::vector < int > vector(state.range(0), 0);

        benchmark::DoNotOptimize(vector);
    }
}

////////////////////////////////////////////////////////////////////////////////

void test_v4(benchmark::State & state)
{
    for (auto element : state) 
    {
        std::vector < std::vector < int > > vector
        (
            state.range(0), std::vector < int > (state.range(1), 0)
        );

        benchmark::DoNotOptimize(vector);
    }
}

////////////////////////////////////////////////////////////////////////////////

void test_v5(benchmark::State & state)
{
    std::vector < int > vector(state.range(0), 0);

    std::ranges::iota(vector, 1);

    for (auto element : state) 
    {
        benchmark::DoNotOptimize(std::ranges::lower_bound(vector, 0));
    }

    state.SetComplexityN(state.range(0));
}

////////////////////////////////////////////////////////////////////////////////

void test_v6(benchmark::State & state)
{
    for (auto element : state) 
    {
        state.SkipWithError("error");

        break;
    }
} 

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v3)->Arg(1);

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v3)->DenseRange(1'000, 5'000, 1'000);

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v3)->RangeMultiplier(2)->Range(128, 1'024);

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v4)->Args({ 1, 2 })->Args({ 2, 4 })->Args({ 3, 6 });

////////////////////////////////////////////////////////////////////////////////

void make_args(::benchmark::Benchmark * benchmark) 
{
    for (auto i = 1; i < 4; ++i)
    {
        benchmark->Args({ i, i * 2 });
    }
}

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v4)->Apply(make_args);

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v5)->RangeMultiplier(2)->Range(1'024, 1'024 << 16)->Complexity();

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v6);

////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////////////////////////////////////////////