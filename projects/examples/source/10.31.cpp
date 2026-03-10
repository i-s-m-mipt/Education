////////////////////////////////////////////////////////

// chapter : Data Structures

////////////////////////////////////////////////////////

// section : Nested Containers

////////////////////////////////////////////////////////

// content : Microbenchmarking
//
// content : Tool lscpu
//
// content : Row-Major and Column-Major Orders

////////////////////////////////////////////////////////

// support : lscpu

////////////////////////////////////////////////////////

#include <vector>

////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto argument = state.range(0);

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
                if (argument == 1) { vector[i][j] = 1; }

                if (argument == 2) { vector[j][i] = 1; }
            }
        }

        benchmark::DoNotOptimize(vector);
    }
}

////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2);

////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////////////////////