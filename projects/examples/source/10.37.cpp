///////////////////////////////////////////////////////////////////////////////////////

// chapter : Programming with Containers

///////////////////////////////////////////////////////////////////////////////////////

// content : Flat Containers
//
// content : Container std::flat_set
//
// content : Microbenchmarking

///////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <flat_set>
#include <iterator>
#include <numeric>
#include <set>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    auto argument = state.range(0);

    std::vector < int > vector(1 << 10, 0);

    std::ranges::iota(vector, 1);

    std::     set < int > set_1(std::begin(vector), std::end(vector));

    std::flat_set < int > set_2(std::begin(vector), std::end(vector));

    for (auto element_1 : state)
    {
        switch (argument)
        {
            case 1 : { for (auto element_2 : set_1) { assert(element_2 > 0); } break; }

            case 2 : { for (auto element_2 : set_2) { assert(element_2 > 0); } break; }
        }

		benchmark::DoNotOptimize(set_1);

        benchmark::DoNotOptimize(set_2);
    }
}

///////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    auto argument = state.range(0);

    std::vector < int > vector(1 << 10, 0);

    std::ranges::iota(vector, 1);

    std::     set < int > set_1(std::begin(vector), std::end(vector));

    std::flat_set < int > set_2(std::begin(vector), std::end(vector));

    for (auto element : state)
    {
        switch (argument)
        {
            case 1 : { set_1.insert(set_1.erase(std::begin(set_1)), 1); break; }

            case 2 : { set_2.insert(set_2.erase(std::begin(set_2)), 1); break; }
        }

		benchmark::DoNotOptimize(set_1);

        benchmark::DoNotOptimize(set_2);
    }
}

///////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1)->Arg(1)->Arg(2);

BENCHMARK(test_v2)->Arg(1)->Arg(2);

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////////