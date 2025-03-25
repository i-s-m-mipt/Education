#include <bit>
#include <cstdint>

#include <benchmark/benchmark.h>

/////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state) // support : compiler-explorer.com
{
    for (auto element : state)
    {
        auto x = 1.0;
        
        benchmark::DoNotOptimize(*reinterpret_cast < char * > (&x));
    }
}

/////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state) // support : compiler-explorer.com
{
    for (auto element : state)
    {
        auto x = 1.0;

        benchmark::DoNotOptimize(*std::bit_cast < char * > (&x));
    }
}

/////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

/////////////////////////////////////////////////////////////////////////

int main()
{
    auto x = 1.0;
    
    [[maybe_unused]] std::uint64_t y = 0;

//  --------------------------------------------------------
    
//  *reinterpret_cast < double * > (&y) = x; // error

//  y = *reinterpret_cast < std::uint64_t * > (&x); // error

//  --------------------------------------------------------

    y = std::bit_cast < std::uint64_t > (x);

//  --------------------------------------------------------

    benchmark::RunSpecifiedBenchmarks();
}