#include <algorithm>
#include <cmath>
#include <cstddef>
#include <execution>
#include <iterator>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

//  ================================================================================================

auto make_vector(std::size_t size)
{
	std::vector < double > vector(size, 0.0);

	std::default_random_engine engine;

	std::uniform_real_distribution distribution(0.0, 1.0);

	auto generator = [&engine, &distribution](){ return distribution(engine); };

	std::ranges::generate(vector, generator);

	return vector;
}

//  ================================================================================================

void test_v1(benchmark::State & state)
{
    auto vector = make_vector(state.range(0));

    for (auto element : state)
    {
        std::for_each
        (
            std::execution::seq, std::begin(vector), std::end(vector), [](auto & x) 
            { 
                x = std::pow(std::sin(x), 2.0) + std::pow(std::cos(x), 2.0); 
            }
        );
    }
}

//  ================================================================================================

void test_v2(benchmark::State & state)
{
    auto vector = make_vector(state.range(0));

    for (auto element : state)
    {
        std::for_each
        (
            std::execution::par, std::begin(vector), std::end(vector), [](auto & x) 
            { 
                x = std::pow(std::sin(x), 2.0) + std::pow(std::cos(x), 2.0); 
            }
        );
    }
}

//  ================================================================================================

void test_v3(benchmark::State & state)
{
    auto vector = make_vector(state.range(0));
    
    for (auto element : state)
    {
        std::for_each
        (
            std::execution::par_unseq, std::begin(vector), std::end(vector), [](auto & x) 
            { 
                x = std::pow(std::sin(x), 2.0) + std::pow(std::cos(x), 2.0);
            }
        );
    }
}

//  ================================================================================================

BENCHMARK(test_v1)->DenseRange(1'000'000, 5'000'000, 1'000'000);
BENCHMARK(test_v2)->DenseRange(1'000'000, 5'000'000, 1'000'000);
BENCHMARK(test_v3)->DenseRange(1'000'000, 5'000'000, 1'000'000);

BENCHMARK_MAIN();