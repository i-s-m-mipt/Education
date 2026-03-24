//////////////////////////////////////////////////////////////////

#include <atomic>
#include <vector>

//////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////////////

struct alignas(1 * 8) Entity_v1 { int x = 0; };

struct alignas(2 * 8) Entity_v2 { int x = 0; };

//////////////////////////////////////////////////////////////////

void test(benchmark::State & state) 
{
    auto argument = state.range(0);

    auto size = 1uz << 10;

    std::vector <               Entity_v1   > entities_v1_1(size);

    std::vector < std::atomic < Entity_v1 > > entities_v1_2(size);

    std::vector <               Entity_v2   > entities_v2_1(size);

    std::vector < std::atomic < Entity_v2 > > entities_v2_2(size);

    Entity_v1 entity_v1(1);

    Entity_v2 entity_v2(1);

    for (auto element : state)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            switch (argument)
            {
                case 1 : { entities_v1_1[i] = entity_v1; break; }

                case 2 : { entities_v1_2[i] = entity_v1; break; }

                case 3 : { entities_v2_1[i] = entity_v2; break; }

                case 4 : { entities_v2_2[i] = entity_v2; break; }
            }
        }

        benchmark::DoNotOptimize(entities_v1_1);

        benchmark::DoNotOptimize(entities_v1_2);

        benchmark::DoNotOptimize(entities_v2_1);

        benchmark::DoNotOptimize(entities_v2_2);
    }
}

//////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2)->Arg(3)->Arg(4);

//////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////////////////////////