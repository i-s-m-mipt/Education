//////////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <cstdint>

//////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    for (auto element : state)
    {
        auto x = 1.0;

        auto y = *reinterpret_cast < char * > (&x); // support : compiler-explorer.com
        
        benchmark::DoNotOptimize(y);
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state) 
{
    for (auto element : state)
    {
        auto x = 1.0;

        auto y = *std::bit_cast < char * > (&x); // support : compiler-explorer.com

        benchmark::DoNotOptimize(y);
    }
}

//////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto x = 1.0;

//  -------------------------------------------------
    
    [[maybe_unused]] std::uint64_t y = 0;

//  -------------------------------------------------
    
//  *reinterpret_cast < double * > (&y) = x; // error

//  -------------------------------------------------

    y = std::bit_cast < std::uint64_t > (x);

//  -------------------------------------------------

    benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////////////////////////////////////////////