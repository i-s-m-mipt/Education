/////////////////////////////////////////////////////////

// chapter : Number Processing

/////////////////////////////////////////////////////////

// section : Random Numbers

/////////////////////////////////////////////////////////

// content : Branch Predictor Microbenchmarking
//
// content : Distribution std::uniform_int_distribution

/////////////////////////////////////////////////////////

#include <cmath>
#include <random>

/////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

/////////////////////////////////////////////////////////

void test(benchmark::State & state) 
{
    std::uniform_int_distribution distribution(1, 1'000);

    std::default_random_engine engine;

    for (auto element : state)
    {
        auto x = 0.0;

        for (auto i = 0uz; i < 1'000; ++i)
        {
            if (distribution(engine) <= state.range(0))
            {
                x += std::pow(std::cos(i), 2);
            }
            else
            {
                x += std::pow(std::sin(i), 2);
            }
        }

        benchmark::DoNotOptimize(x);
    }
}

/////////////////////////////////////////////////////////

BENCHMARK(test)->DenseRange(0, 1'000, 50);

/////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

/////////////////////////////////////////////////////////