////////////////////////////////////////

#include <iterator>
#include <set>

////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    for (auto element : state)
    {
        std::set < int > set;

		auto iterator = std::begin(set);

		for (auto i = 1'000; i > 0; --i)
		{
			set.insert(iterator, i);

			iterator = std::begin(set);
		}

		benchmark::DoNotOptimize(set);
    }
}

////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    for (auto element : state)
    {
        std::set < int > set;

		auto iterator = std::begin(set);

		for (auto i = 1'000; i > 0; --i)
		{
			set.insert(iterator, i);

			iterator = std::end(set);
		}

		benchmark::DoNotOptimize(set);
    }
}

////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////