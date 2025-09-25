//////////////////////////////////////////////

// support : lscpu | grep L1d

//////////////////////////////////////////////

#include <vector>

//////////////////////////////////////////////

#include <benchmark/benchmark.h>

//////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    auto size = 32'768uz / sizeof(int);

    std::vector < std::vector < int > > vector
    (
        size, std::vector < int > (size, 0)
    );

    for (auto element : state)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            for (auto j = 0uz; j < size; ++j)
            {
                vector[i][j] = 1;
            }
        }

        benchmark::DoNotOptimize(vector);
    }
}

//////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    auto size = 32'768uz / sizeof(int);

    std::vector < std::vector < int > > vector
    (
        size, std::vector < int > (size, 0)
    );

    for (auto element : state)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            for (auto j = 0uz; j < size; ++j)
            {
                vector[j][i] = 1;
            }
        }

        benchmark::DoNotOptimize(vector);
    }
}

//////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

//////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////