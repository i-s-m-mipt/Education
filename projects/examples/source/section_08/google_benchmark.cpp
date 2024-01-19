#include <exception>
#include <iostream>
#include <stdexcept>

#include <benchmark/benchmark.h>

void test_1(benchmark::State & state) 
{
    for (auto _ : state)
    {
        auto s = 0;
        auto x = 0;

        benchmark::DoNotOptimize(s);
        benchmark::DoNotOptimize(x);

        while (true) if (s += ++x; x == 100) break;
    }
}

void test_2(benchmark::State & state) 
{
    for (auto _ : state)
    {
        try
        {
            auto s = 0;
            auto x = 0;

            benchmark::DoNotOptimize(s);
            benchmark::DoNotOptimize(x);

            while (true) if (s += ++x; x == 100) break;
        }
        catch (const std::exception & exception)
        {
            std::cerr << exception.what() << std::endl;
        }
    }
}

void test_3(benchmark::State & state)
{
    for (auto _ : state)
    {
        try
        {
            auto s = 0;
            auto x = 0;

            benchmark::DoNotOptimize(s);
            benchmark::DoNotOptimize(x);

            while (true) if (s += ++x; x == 100) throw std::exception("exit");
        }
        catch (...) {}
    }
}

BENCHMARK(test_1);
BENCHMARK(test_2);
BENCHMARK(test_3);

BENCHMARK_MAIN();