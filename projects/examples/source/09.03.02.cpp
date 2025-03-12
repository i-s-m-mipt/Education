#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////////

struct Entity_v1 { std::int8_t data_1 = 0; std::int32_t data_2 = 0; std::int16_t data_3 = 0; };

struct Entity_v2 { std::int8_t data_1 = 0; std::int16_t data_2 = 0; std::int32_t data_3 = 0; };

///////////////////////////////////////////////////////////////////////////////////////////////

struct             Entity_v3 { std::int8_t data = 0; };

struct alignas(64) Entity_v4 { std::int8_t data = 0; };

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	std::vector < Entity_v3 > entities(1'000);
	
    for (auto element : state)
    {
		for (auto i = 0uz; i < std::size(entities); ++i) 
		{
			entities[i].data = 1;
		}

		benchmark::DoNotOptimize(entities);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	std::vector < Entity_v4 > entities(1'000);
	
    for (auto element : state)
    {
		for (auto i = 0uz; i < std::size(entities); ++i) 
		{
			entities[i].data = 1;
		}

		benchmark::DoNotOptimize(entities);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(sizeof(Entity_v1) == 12 && alignof(Entity_v1) == 4);

	static_assert(sizeof(Entity_v2) ==  8 && alignof(Entity_v2) == 4);

//  ------------------------------------------------------------------

    benchmark::RunSpecifiedBenchmarks();
}