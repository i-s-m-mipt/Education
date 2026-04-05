/////////////////////////////////////////////////////////

// chapter : Containers

/////////////////////////////////////////////////////////

// section : Nested Containers

/////////////////////////////////////////////////////////

// content : Row-Major and Column-Major Orders
//
// content : Microbenchmarking

/////////////////////////////////////////////////////////

#include <vector>

/////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

/////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto argument = state.range(0);

    auto size = 1uz << 10;

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
                switch (argument)
                {
                    case 1 : { vector[i][j] = 1; break; }

                    case 2 : { vector[j][i] = 1; break; }
                }
            }
        }

        benchmark::DoNotOptimize(vector);
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