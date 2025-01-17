#include <algorithm>
#include <cmath>
#include <exception>
#include <numeric>
#include <stdexcept>
#include <vector>

#include <benchmark/benchmark.h>

//  ================================================================================================

void test_v1(benchmark::State & state) 
{
    for (auto element : state)
    {
        auto result = 0.0;

		for (auto i = 0uz; i < 1'000; ++i)
		{
			result += std::pow(std::sin(i), 2.0) + std::pow(std::cos(i), 2.0);
		}

        benchmark::DoNotOptimize(result);
    }
}

//  ================================================================================================

void test_v2(benchmark::State & state) 
{
    for (auto element : state)
    {
        auto result = 0.0;

        try 
        {
            for (auto i = 0uz; i < 1'000; ++i)
            {
                result += std::pow(std::sin(i), 2.0) + std::pow(std::cos(i), 2.0);
            }
        }
        catch (...) {}

        benchmark::DoNotOptimize(result);
    }
}

//  ================================================================================================

void test_v3(benchmark::State & state)
{
    for (auto element : state)
    {
        auto result = 0.0;

        try
        {
            for (auto i = 0uz; true; ++i)
            {
                result += std::pow(std::sin(i), 2.0) + std::pow(std::cos(i), 2.0);

                if (i >= 1'000) 
                {
                    throw std::runtime_error("error");
                }
            }
        }
        catch (...) {}

        benchmark::DoNotOptimize(result);
    }
}

//  ================================================================================================

void test_v4(benchmark::State & state) 
{
    for (auto element : state) 
    {
        std::vector < int > vector(state.range(0), 0);

        benchmark::DoNotOptimize(vector);
    }
}

//  ================================================================================================

void test_v5(benchmark::State & state)
{
    for (auto element : state) 
    {
        std::vector < std::vector < int > > vector
        (
            state.range(0), std::vector < int > (state.range(1), 0)
        );

        benchmark::DoNotOptimize(vector);
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

void test_v6(benchmark::State & state)
{
    std::vector < int > vector(state.range(0), 0);

    std::ranges::iota(vector, 1);

    for (auto element : state) 
    {
        benchmark::DoNotOptimize(std::ranges::lower_bound(vector, 0));
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

void test_v7(benchmark::State & state)
{
    for (auto element : state) 
    {
        state.SkipWithError("error");

        break;
    }
} 

//  ================================================================================================

BENCHMARK(test_v1);

BENCHMARK(test_v2);

BENCHMARK(test_v3);

BENCHMARK(test_v4)->Arg(1);

BENCHMARK(test_v4)->DenseRange(0, 5'000, 1'000);

BENCHMARK(test_v4)->RangeMultiplier(2)->Range(128, 1'024);

BENCHMARK(test_v5)->Args({ 1, 2 })->Args({ 2, 4 })->Args({ 3, 6 });

void make_args(benchmark::internal::Benchmark * benchmark) 
{
    for (auto i = 1; i < 4; ++i) 
    {
        benchmark->Args({ i, i * 2 });
    }
}

BENCHMARK(test_v5)->Apply(make_args);

BENCHMARK(test_v6)->RangeMultiplier(2)->Range(1'024, 1'024 << 16)->Complexity();

BENCHMARK(test_v7);

BENCHMARK_MAIN();