#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

#include <benchmark/benchmark.h>

// =================================================================================================

void test_1(benchmark::State & state) 
{
    for (auto _ : state) // note: range-based for loop recommended in documentation
    {
        auto s = 0, x = 0;

        while (true) if (s += ++x; x == 100) break;

        benchmark::DoNotOptimize(s);
    }
}

// =================================================================================================

void test_2(benchmark::State & state) 
{
    for (auto _ : state)
    {
        try // note: zero-overhead principle in exceptions
        {
            auto s = 0, x = 0;
            
            while (true) if (s += ++x; x == 100) break;

            benchmark::DoNotOptimize(s);
        }
        catch (const std::exception & exception)
        {
            std::cerr << exception.what() << '\n';
        }
    }
}

// =================================================================================================

void test_3(benchmark::State & state)
{
    for (auto _ : state)
    {
        try
        {
            auto s = 0, x = 0;

            while (true)
            {
                if (s += ++x; x == 100)
                {
                    throw std::runtime_error("exit"); // note: slow exit
                }
            }

            benchmark::DoNotOptimize(s);
        }
        catch (...) {}
    }
}

// =================================================================================================

void test_4(benchmark::State & state) 
{
    for (auto _ : state) 
    {
        std::vector < int > vector_1d(state.range(0), 0);

        benchmark::DoNotOptimize(vector_1d);
    }
}

// =================================================================================================

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

// =================================================================================================

void test_6(benchmark::State & state)
{
    std::vector < int > vector(state.range(0), 0);

    std::iota(std::begin(vector), std::end(vector), 1); // note: generate range 1, 2, 3, ...

    for (auto _ : state) 
    {
        benchmark::DoNotOptimize(std::ranges::lower_bound(std::as_const(vector), 0));
    }

    state.SetComplexityN(state.range(0)); // note: try to search 1 instead of 0 in lower_bound
}

// =================================================================================================

void test_7(benchmark::State & state)
{
    for (auto _ : state) 
    {
        state.SkipWithError("test failed");

        break; // note: required to prevent all further iterations.
    }
} 

// =================================================================================================

BENCHMARK(test_1); // note: fast, no exceptions

BENCHMARK(test_2); // note: fast, no exceptions handling

BENCHMARK(test_3); // note: slower than tests 1 and 2 due to exceptions handling

BENCHMARK(test_4)->Arg(1); // note: single test with 1 argument

BENCHMARK(test_4)->DenseRange(0, 1024, 256); // note: 0, 256, 512, ...

BENCHMARK(test_4)->RangeMultiplier(2)->Range(128, 1024); // note: 128, 256, 512, ...

BENCHMARK(test_5)->Args({ 1, 2 })->Args({ 2, 4 })->Args({ 3, 6 });

void make_arguments(benchmark::internal::Benchmark * benchmark) 
{
    for (auto i = 1; i < 4; ++i) benchmark->Args({ i, i * 2 });
}

BENCHMARK(test_5)->Apply(make_arguments);

BENCHMARK(test_6)->RangeMultiplier(2)->Range(1024, 1024 << 16)->Complexity(); // note: lgN

BENCHMARK(test_7); // note: exited with error

BENCHMARK_MAIN();