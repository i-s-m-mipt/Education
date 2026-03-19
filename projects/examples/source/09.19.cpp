/////////////////////////////////////////////////////////

// chapter : Memory Management

/////////////////////////////////////////////////////////

// section : Dynamic Memory

/////////////////////////////////////////////////////////

// content : Type Specifier alignas
//
// content : Microbenchmarking

/////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

/////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

/////////////////////////////////////////////////////////

struct            Entity_v1 { std::int8_t x = 0; };

struct alignas(8) Entity_v2 { std::int8_t x = 0; };

/////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto argument = state.range(0);

	auto size = 1'000'000uz;

	std::vector < Entity_v1 > entities_v1(size);

	std::vector < Entity_v2 > entities_v2(size);
	
    for (auto element : state)
    {
		for (auto i = 0uz; i < size; ++i)
        {
            switch (argument)
            {
                case 1 : { entities_v1[i].x = 1; break; }

                case 2 : { entities_v2[i].x = 1; break; }
            }
        }

        benchmark::DoNotOptimize(entities_v1);

        benchmark::DoNotOptimize(entities_v2);
    }
}

/////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2);

/////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

/////////////////////////////////////////////////////////