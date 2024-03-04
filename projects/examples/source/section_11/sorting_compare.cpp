#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>

#include <benchmark/benchmark.h>

using Clock = std::chrono::steady_clock;

void test_1(benchmark::State & state) 
{
    for (auto _ : state)
    {
        std::array < int, 100'000 > array; // note: template parameter instead of state.range(0)

        std::iota(std::begin(array), std::end(array), 1); // note: writes 1, 2, 3, ...

        auto start = Clock::now();

        std::ranges::sort(array, std::greater());

        state.SetIterationTime(std::chrono::duration_cast < std::chrono::duration < double > > (Clock::now() - start).count());

        benchmark::DoNotOptimize(array);
    }
}

void test_2(benchmark::State & state) 
{
    for (auto _ : state)
    {
        std::vector < int > vector(state.range(0));

        std::iota(std::begin(vector), std::end(vector), 1); // note: writes 1, 2, 3, ...

        auto start = Clock::now();

        std::ranges::sort(vector, std::greater());

        state.SetIterationTime(std::chrono::duration_cast < std::chrono::duration < double > > (Clock::now() - start).count());

        benchmark::DoNotOptimize(vector);
    }
}

void test_3(benchmark::State & state) 
{
    for (auto _ : state)
    {
        std::deque < int > deque(state.range(0));

        std::iota(std::begin(deque), std::end(deque), 1); // note: writes 1, 2, 3, ...

        auto start = Clock::now();

        std::ranges::sort(deque, std::greater());

        state.SetIterationTime(std::chrono::duration_cast < std::chrono::duration < double > > (Clock::now() - start).count());

        benchmark::DoNotOptimize(deque);
    }
}

void test_4(benchmark::State & state) 
{
    for (auto _ : state)
    {
        std::list < int > list(state.range(0));

        std::iota(std::begin(list), std::end(list), 1); // note: writes 1, 2, 3, ...

        auto start = Clock::now();

        list.sort(std::greater());

        state.SetIterationTime(std::chrono::duration_cast < std::chrono::duration < double > > (Clock::now() - start).count());

        benchmark::DoNotOptimize(list);
    }
}

void test_5(benchmark::State & state) 
{
    for (auto _ : state)
    {
        std::forward_list < int > forward_list(state.range(0));

        std::iota(std::begin(forward_list), std::end(forward_list), 1); // note: writes 1, 2, 3, ...

        auto start = Clock::now();

        forward_list.sort(std::greater());

        state.SetIterationTime(std::chrono::duration_cast < std::chrono::duration < double > > (Clock::now() - start).count());

        benchmark::DoNotOptimize(forward_list);
    }
}

BENCHMARK(test_1); 
BENCHMARK(test_2)->Arg(100'000); // note: slower
BENCHMARK(test_3)->Arg(100'000); // note: slower
BENCHMARK(test_4)->Arg(100'000); // note: slower
BENCHMARK(test_5)->Arg(100'000); // note: slower

BENCHMARK_MAIN();