/////////////////////////////////////////

#include <algorithm>
#include <set>
#include <vector>

/////////////////////////////////////////

#include <benchmark/benchmark.h>

/////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    for (auto element : state)
    {
        std::vector < int > vector;

		for (auto i = 1'000; i > 0; --i)
		{
			vector.push_back(i);
		}

		std::ranges::sort(vector);

		benchmark::DoNotOptimize(vector);
    }
}

/////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    for (auto element : state)
    {
        std::set < int > set;

		for (auto i = 1'000; i > 0; --i)
		{
			set.insert(i);
		}

		benchmark::DoNotOptimize(set);
    }
}

/////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

/////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

/////////////////////////////////////////