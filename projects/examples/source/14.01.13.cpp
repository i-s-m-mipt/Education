////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <execution>
#include <iterator>
#include <random>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////////////////////

auto make_vector(std::size_t size)
{
	std::vector < double > vector(size, 0);

    std::uniform_real_distribution distribution(0.0, 1.0);

	std::default_random_engine engine;

    auto lambda = [&engine, &distribution](){ return distribution(engine); };

	std::ranges::generate(vector, lambda);

	return vector;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void handler(double & x)
{
    x = std::pow(std::sin(x), 2) + std::pow(std::cos(x), 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    auto vector = make_vector(1'000'000);

    for (auto element : state)
    {
        std::for_each(std::execution::seq, std::begin(vector), std::end(vector), handler);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    auto vector = make_vector(1'000'000);

    for (auto element : state)
    {
        std::for_each(std::execution::par, std::begin(vector), std::end(vector), handler);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

void test_v3(benchmark::State & state)
{
    auto vector = make_vector(1'000'000);
    
    for (auto element : state)
    {
        std::for_each(std::execution::par_unseq, std::begin(vector), std::end(vector), handler);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

void test_v4(benchmark::State & state)
{
    auto vector = make_vector(1'000'000);
    
    for (auto element : state)
    {
        std::for_each(std::execution::unseq, std::begin(vector), std::end(vector), handler);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

BENCHMARK(test_v3);

BENCHMARK(test_v4);

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////////////////////////////////////////////////////////////