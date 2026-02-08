// content : Type Alias std::int8_t

////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////

struct Entity_v1 { std::int8_t x = 0; std::int32_t y = 0; std::int16_t z = 0; };

struct Entity_v2 { std::int8_t x = 0; std::int16_t y = 0; std::int32_t z = 0; };

////////////////////////////////////////////////////////////////////////////////

struct            Entity_v3 { std::int8_t x = 0; };

struct alignas(8) Entity_v4 { std::int8_t x = 0; };

////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
	auto size = 1'000'000uz;

	std::vector < Entity_v3 > entities_v3(size);

	std::vector < Entity_v4 > entities_v4(size);
	
    for (auto element : state)
    {
		for (auto i = 0uz; i < size; ++i)
        {
            if (state.range(0) == 1) { entities_v3[i].x = 1; }

            if (state.range(0) == 2) { entities_v4[i].x = 1; }
        }

        benchmark::DoNotOptimize(entities_v3);

        benchmark::DoNotOptimize(entities_v4);
    }
}

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2);

////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(sizeof(Entity_v1) == 12 && alignof(Entity_v1) == 4);

	static_assert(sizeof(Entity_v2) ==  8 && alignof(Entity_v2) == 4);

//  ------------------------------------------------------------------

    benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////////////////////////////////////////////