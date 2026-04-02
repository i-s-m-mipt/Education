///////////////////////////////////////////////////////////

// chapter : Arithmetic

///////////////////////////////////////////////////////////

// section : Random Numbers

///////////////////////////////////////////////////////////

// content : Dynamic Branch Prediction
//
// content : Microbenchmarking
//
// content : Distribution std::uniform_int_distribution

///////////////////////////////////////////////////////////

#include <cmath>
#include <random>

///////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////

void test(benchmark::State & state) 
{
    auto argument = state.range(0);

    std::uniform_int_distribution distribution(1, 1 << 10);

    std::default_random_engine engine;

    for (auto element : state)
    {
        auto x = 0.0;

        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            if (distribution(engine) <= argument)
            {
                x += std::pow(std::sin(i), 2);
            }
            else
            {
                x += std::pow(std::cos(i), 2);
            }
        }

        benchmark::DoNotOptimize(x);
    }
}

///////////////////////////////////////////////////////////

BENCHMARK(test)->DenseRange(0, 1 << 10, 128);

///////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////