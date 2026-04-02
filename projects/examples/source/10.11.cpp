////////////////////////////////////////////////////////

// chapter : Containers

////////////////////////////////////////////////////////

// section : Sequential Containers

////////////////////////////////////////////////////////

// content : Microbenchmarking

////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>

////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////

#include "08.35.hpp"

////////////////////////////////////////////////////////

void test_v1(benchmark::State & state) 
{
    auto const size = 1uz << 20;

    std::array < int, size > array = {};

    for (auto element : state)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            array[i] = size - i;
        }

        Timer timer;

        std::ranges::sort(array);

        state.SetIterationTime(timer.elapsed().count());

        benchmark::DoNotOptimize(array);
    }
}

////////////////////////////////////////////////////////

void test_v2(benchmark::State & state) 
{
    auto size = 1uz << 20;

    std::vector < int > vector(size, 0);

    for (auto element : state)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            vector[i] = size - i;
        }

        Timer timer;

        std::ranges::sort(vector);

        state.SetIterationTime(timer.elapsed().count());

        benchmark::DoNotOptimize(vector);
    }
}

////////////////////////////////////////////////////////

void test_v3(benchmark::State & state) 
{
    auto size = 1uz << 20;

    std::deque < int > deque(size, 0);

    for (auto element : state)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            deque[i] = size - i;
        }

        Timer timer;

        std::ranges::sort(deque);

        state.SetIterationTime(timer.elapsed().count());

        benchmark::DoNotOptimize(deque);
    }
}

////////////////////////////////////////////////////////

void test_v4(benchmark::State & state) 
{
    auto size = 1uz << 20;

    std::list < int > list(size, 0);

    for (auto element : state)
    {
        for (auto x = 0; auto & element : list)
        {
            element = size + 1 - ++x;
        }

        Timer timer;

        list.sort();

        state.SetIterationTime(timer.elapsed().count());

        benchmark::DoNotOptimize(list);
    }
}

////////////////////////////////////////////////////////

void test_v5(benchmark::State & state) 
{
    auto size = 1uz << 20;

    std::forward_list < int > list(size, 0);

    for (auto element : state)
    {
        for (auto x = 0; auto & element : list)
        {
            element = size + 1 - ++x;
        }

        Timer timer;

        list.sort();

        state.SetIterationTime(timer.elapsed().count());
        
        benchmark::DoNotOptimize(list);
    }
}

////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

BENCHMARK(test_v3);

BENCHMARK(test_v4);

BENCHMARK(test_v5);

////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////////////////////