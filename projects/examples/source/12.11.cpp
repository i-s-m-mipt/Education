//////////////////////////////////////////////////////////

// chapter : Strings

//////////////////////////////////////////////////////////

// section : Strings

//////////////////////////////////////////////////////////

// content : Microbenchmarking

//////////////////////////////////////////////////////////

#include <string>
#include <string_view>

//////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    auto argument = state.range(0);

    std::string string_1(4 << 10, 'a');

    for (auto element : state)
    {
        auto string_2 = string_1.substr(0, argument);

        benchmark::DoNotOptimize(string_2);
    }
}

//////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    auto argument = state.range(0);

    std::string string(4 << 10, 'a');

    std::string_view view_1 = string;

    for (auto element : state)
    {
        auto view_2 = view_1.substr(0, argument);

        benchmark::DoNotOptimize(view_2);
    }
}

//////////////////////////////////////////////////////////

BENCHMARK(test_v1)->DenseRange(1 << 10, 4 << 10, 1 << 10);

BENCHMARK(test_v2)->DenseRange(1 << 10, 4 << 10, 1 << 10);

//////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////////////////