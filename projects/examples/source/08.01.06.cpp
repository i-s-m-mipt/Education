///////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

///////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////

struct Entity_v1 { std::uint32_t x : 15 = 0, y : 17 = 0; };

struct Entity_v2 { std::uint32_t x      = 0, y      = 0; };

///////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    std::vector < Entity_v1 > entities(1'000);

    for (auto element : state)
    {
        for (auto i = 0uz; i < std::size(entities); ++i)
        {
            entities[i].x = i + 1;

            entities[i].y = i + 1;
        }
    }
}

///////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    std::vector < Entity_v2 > entities(1'000);

    for (auto element : state)
    {        
        for (auto i = 0uz; i < std::size(entities); ++i)
        {
            entities[i].x = i + 1;

            entities[i].y = i + 1;
        }
    }
}

///////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

///////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////