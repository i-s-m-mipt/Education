#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

#include <benchmark/benchmark.h>

//  ================================================================================================

void test_v1(benchmark::State & state) 
{
    for (auto value : state)
    {
        auto result = 0.0;

        for (auto i = 0uz; i < 1000; ++i) 
        {
            result += std::sin(i);
        }

        benchmark::DoNotOptimize(result);
    }
}

//  ================================================================================================

void test_v2(benchmark::State & state) 
{
    for (auto value : state)
    {
        auto result = 0.0;

        try 
        {
            for (auto i = 0uz; i < 1000; ++i) 
            {
                result += std::sin(i);
            }
        }
        catch (...) {}

        benchmark::DoNotOptimize(result);
    }
}

//  ================================================================================================

void test_v3(benchmark::State & state)
{
    for (auto value : state)
    {
        auto result = 0.0;

        try
        {
            for (auto i = 0uz; ; ++i)
            {
                result += std::sin(i);

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
    for (auto value : state) 
    {
        std::vector < int > vector_1d(state.range(0), 0);

        benchmark::DoNotOptimize(vector_1d);
    }
}

//  ================================================================================================

void test_v5(benchmark::State & state)
{
    for (auto value : state) 
    {
        std::vector < std::vector < int > > vector_2d(state.range(0), 
                      std::vector < int >            (state.range(1), 0));

        benchmark::DoNotOptimize(vector_2d);
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

void test_v6(benchmark::State & state)
{
    std::vector < int > vector(state.range(0), 0);

    std::ranges::iota(vector, 1);

    for (auto value : state) 
    {
        benchmark::DoNotOptimize(std::ranges::lower_bound(std::as_const(vector), 0));
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

void test_v7(benchmark::State & state)
{
    for (auto value : state) 
    {
        state.SkipWithError("test failed");

        break;
    }
} 

//  ================================================================================================

BENCHMARK(test_v1);

BENCHMARK(test_v2);

BENCHMARK(test_v3);

BENCHMARK(test_v4)->Arg(1);

BENCHMARK(test_v4)->DenseRange(0, 1024, 256);

BENCHMARK(test_v4)->RangeMultiplier(2)->Range(128, 1024);

BENCHMARK(test_v5)->Args({ 1, 2 })->Args({ 2, 4 })->Args({ 3, 6 });

void make_args(benchmark::internal::Benchmark * benchmark) 
{
    for (auto i = 1; i < 4; ++i) 
    {
        benchmark->Args({ i, i * 2 });
    }
}

BENCHMARK(test_v5)->Apply(make_args);

BENCHMARK(test_v6)->RangeMultiplier(2)->Range(1024, 1024 << 16)->Complexity();

BENCHMARK(test_v7);

BENCHMARK_MAIN();