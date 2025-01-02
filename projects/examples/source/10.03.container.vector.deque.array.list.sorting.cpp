#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <forward_list>
#include <functional>
#include <list>
#include <numeric>
#include <vector>

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state) 
{
    for (auto element : state)
    {
        std::array < int, 100'000 > array;

        for (auto i = std::size(array); auto & element : array)
        {
            element = static_cast < int > (i--);
        }  

        auto start = std::chrono::steady_clock::now();

        std::ranges::sort(array);

        auto delta = std::chrono::steady_clock::now() - start;

        state.SetIterationTime
        (
            std::chrono::duration_cast < std::chrono::duration < double > > (delta).count()
        );

        benchmark::DoNotOptimize(array);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state) 
{
    for (auto element : state)
    {
        std::vector < int > vector(100'000, 0);

        for (auto i = std::size(vector); auto & element : vector)
        {
            element = static_cast < int > (i--);
        }  

        auto start = std::chrono::steady_clock::now();

        std::ranges::sort(vector);

        auto delta = std::chrono::steady_clock::now() - start;

        state.SetIterationTime
        (
            std::chrono::duration_cast < std::chrono::duration < double > > (delta).count()
        );

        benchmark::DoNotOptimize(vector);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

void test_v3(benchmark::State & state) 
{
    for (auto element : state)
    {
        std::deque < int > deque(100'000, 0);

        for (auto i = std::size(deque); auto & element : deque)
        {
            element = static_cast < int > (i--);
        }  

        auto start = std::chrono::steady_clock::now();

        std::ranges::sort(deque);

        auto delta = std::chrono::steady_clock::now() - start;

        state.SetIterationTime
        (
            std::chrono::duration_cast < std::chrono::duration < double > > (delta).count()
        );

        benchmark::DoNotOptimize(deque);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

void test_v4(benchmark::State & state) 
{
    for (auto element : state)
    {
        std::list < int > list(100'000, 0);

        for (auto i = std::size(list); auto & element : list)
        {
            element = static_cast < int > (i--);
        }

        auto start = std::chrono::steady_clock::now();

        list.sort();

        auto delta = std::chrono::steady_clock::now() - start;

        state.SetIterationTime
        (
            std::chrono::duration_cast < std::chrono::duration < double > > (delta).count()
        );

        benchmark::DoNotOptimize(list);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

void test_v5(benchmark::State & state) 
{
    for (auto element : state)
    {
        auto size = 100'000uz;

        std::forward_list < int > forward_list(size, 0);

        for (auto i = size; auto & element : forward_list)
        {
            element = static_cast < int > (i--);
        } 

        auto start = std::chrono::steady_clock::now();

        forward_list.sort();

        auto delta = std::chrono::steady_clock::now() - start;

        state.SetIterationTime
        (
            std::chrono::duration_cast < std::chrono::duration < double > > (delta).count()
        );
        
        benchmark::DoNotOptimize(forward_list);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1); 
BENCHMARK(test_v2);
BENCHMARK(test_v3);
BENCHMARK(test_v4);
BENCHMARK(test_v5);

BENCHMARK_MAIN();