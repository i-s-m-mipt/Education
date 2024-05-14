#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

#include <benchmark/benchmark.h>

//  ================================================================================================

void test_1(benchmark::State & state) 
{
    for (auto _ : state)
    {
        auto result = 0.0;

        for (std::size_t i = 0; i < 1000; ++i) 
        {
            result += std::sin(i);
        }

        benchmark::DoNotOptimize(result);
    }
}

//  ================================================================================================

void test_2(benchmark::State & state) 
{
    for (auto _ : state)
    {
        auto result = 0.0;

        try 
        {
            for (std::size_t i = 0; i < 1000; ++i) 
            {
                result += std::sin(i);
            }
        }
        catch (const std::exception & exception)
        {
            std::cerr << exception.what() << '\n';
        }

        benchmark::DoNotOptimize(result);
    }
}

//  ================================================================================================

void test_3(benchmark::State & state)
{
    for (auto _ : state)
    {
        auto result = 0.0;

        try
        {
            for (std::size_t i = 0; ; ++i)
            {
                result += std::sin(i);

                if (i >= 1000) throw std::runtime_error("error");
            }
        }
        catch (...) {}

        benchmark::DoNotOptimize(result);
    }
}

//  ================================================================================================

void test_4(benchmark::State & state) 
{
    for (auto _ : state) 
    {
        std::vector < int > vector_1d(state.range(0), 0);

        benchmark::DoNotOptimize(vector_1d);
    }
}

//  ================================================================================================

void test_5(benchmark::State & state)
{
    for (auto _ : state) 
    {
        std::vector < std::vector < int > > vector_2d(state.range(0), 
                      std::vector < int >            (state.range(1), 0));

        benchmark::DoNotOptimize(vector_2d);
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

void test_6(benchmark::State & state)
{
    std::vector < int > vector(state.range(0), 0);

    std::iota(std::begin(vector), std::end(vector), 1);

    for (auto _ : state) 
    {
        benchmark::DoNotOptimize(std::ranges::lower_bound(std::as_const(vector), 0));
    }

    state.SetComplexityN(state.range(0));
}

//  ================================================================================================

void test_7(benchmark::State & state)
{
    for (auto _ : state) 
    {
        state.SkipWithError("test failed");

        break;
    }
} 

//  ================================================================================================

BENCHMARK(test_1);

BENCHMARK(test_2);

BENCHMARK(test_3);

BENCHMARK(test_4)->Arg(1);

BENCHMARK(test_4)->DenseRange(0, 1024, 256);

BENCHMARK(test_4)->RangeMultiplier(2)->Range(128, 1024);

BENCHMARK(test_5)->Args({ 1, 2 })->Args({ 2, 4 })->Args({ 3, 6 });

void make_arguments(benchmark::internal::Benchmark * benchmark) 
{
    for (auto i = 1; i < 4; ++i) benchmark->Args({ i, i * 2 });
}

BENCHMARK(test_5)->Apply(make_arguments);

BENCHMARK(test_6)->RangeMultiplier(2)->Range(1024, 1024 << 16)->Complexity();

BENCHMARK(test_7);

//  ================================================================================================

BENCHMARK_MAIN();