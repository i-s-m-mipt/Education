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
        std::array < int, 100'000 > array = {};

        for (auto i = 0uz; i < std::size(array); ++i)
        {
            array[i] = std::size(array) - i;
        }

        auto begin = std::chrono::steady_clock::now();

        std::ranges::sort(array);

        auto delta = std::chrono::steady_clock::now() - begin;

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

        for (auto i = 0uz; i < std::size(vector); ++i)
        {
            vector[i] = std::size(vector) - i;
        }

        auto begin = std::chrono::steady_clock::now();

        std::ranges::sort(vector);

        auto delta = std::chrono::steady_clock::now() - begin;

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

        for (auto i = 0uz; i < std::size(deque); ++i)
        {
            deque[i] = std::size(deque) - i;
        } 

        auto begin = std::chrono::steady_clock::now();

        std::ranges::sort(deque);

        auto delta = std::chrono::steady_clock::now() - begin;

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

        for (auto x = 0; auto & element : list)
        {
            element = std::size(list) - x++;
        } 

        auto begin = std::chrono::steady_clock::now();

        list.sort();

        auto delta = std::chrono::steady_clock::now() - begin;

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

        std::forward_list < int > list(size, 0);

        for (auto x = 0; auto & element : list)
        {
            element = size - x++;
        } 

        auto begin = std::chrono::steady_clock::now();

        list.sort();

        auto delta = std::chrono::steady_clock::now() - begin;

        state.SetIterationTime
        (
            std::chrono::duration_cast < std::chrono::duration < double > > (delta).count()
        );
        
        benchmark::DoNotOptimize(list);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

BENCHMARK(test_v3);

BENCHMARK(test_v4);

BENCHMARK(test_v5);

BENCHMARK_MAIN();