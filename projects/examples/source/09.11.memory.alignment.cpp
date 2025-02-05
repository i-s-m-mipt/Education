#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////////

struct             Entity_v1 { std::uint8_t x = 0; std::uint32_t y = 0; std::uint16_t z = 0; };

struct             Entity_v2 { std::uint8_t x = 0; std::uint16_t z = 0; std::uint32_t y = 0; };

struct alignas( 8) Entity_v3 { std::uint8_t x = 0; std::uint16_t z = 0; std::uint32_t y = 0; };

struct             Entity_v5 { std::uint8_t x = 0; };

struct alignas(64) Entity_v6 { std::uint8_t x = 0; };

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	std::vector < Entity_v5 > entities(1'000);
	
    for (auto element : state)
    {
		entities.front().x = 1;

		for (auto i = 1uz; i < std::size(entities); ++i) 
		{
			entities[i].x = entities[i - 1].x + 1;
		}

		benchmark::DoNotOptimize(entities);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	std::vector < Entity_v6 > entities(1'000);
	
    for (auto element : state)
    {
		entities.front().x = 1;

		for (auto i = 1uz; i < std::size(entities); ++i) 
		{
			entities[i].x = entities[i - 1].x + 1;
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
	{
		static_assert(std::alignment_of_v < double > == 8);
	}

//  ----------------------------------------------------------------------

	{
		static_assert(sizeof(Entity_v1) == 12 && alignof(Entity_v1) == 4);

		static_assert(sizeof(Entity_v2) ==  8 && alignof(Entity_v2) == 4);

		static_assert(sizeof(Entity_v3) ==  8 && alignof(Entity_v3) == 8);
	}

//  ----------------------------------------------------------------------

	{
        benchmark::RunSpecifiedBenchmarks();
    }
}