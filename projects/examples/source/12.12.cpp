///////////////////////////////////////////////////////////////////

#include <string>
#include <string_view>

///////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    std::string string(65'536, 'a');

    for (auto element : state)
    {
        benchmark::DoNotOptimize(string.substr(0, state.range(0)));
    }

    state.SetComplexityN(state.range(0));
}

///////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    std::string string(65'536, 'a');

    std::string_view view = string;

    for (auto element : state)
    {
        benchmark::DoNotOptimize(view.substr(0, state.range(0)));
    }

    state.SetComplexityN(state.range(0));
}

///////////////////////////////////////////////////////////////////

BENCHMARK(test_v1)->DenseRange(8'192, 65'537, 8'192)->Complexity();

BENCHMARK(test_v2)->DenseRange(8'192, 65'537, 8'192)->Complexity();

///////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////