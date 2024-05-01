#include <algorithm>
#include <cmath>
#include <execution>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

#include <chrono>
#include <iostream>

#include <benchmark/benchmark.h>

// =================================================================================================

[[nodiscard]] inline std::vector < double > make_vector(std::size_t size)
{
	std::vector < double > vector(size);

	std::mt19937_64 engine(42);

	std::uniform_real_distribution distribution(0.0, 1.0);

	const auto generator = [&engine, &distribution](){ return distribution(engine); };

	std::ranges::generate(vector, generator);

	return vector;
}

// =================================================================================================

void test_1(benchmark::State & state) // note: usual
{
    auto vector = make_vector(state.range(0));

    for (auto _ : state)
    {
        std::for_each(std::execution::seq, std::begin(vector), std::end(vector),

			[](auto & x) constexpr noexcept { x = std::sin(std::cos(x)); });
    }
}

// =================================================================================================

void test_2(benchmark::State & state) // note: fast
{
    auto vector = make_vector(state.range(0));

    for (auto _ : state)
    {
        std::for_each(std::execution::par, std::begin(vector), std::end(vector),

			[](auto & x) constexpr noexcept { x = std::sin(std::cos(x)); });
    }
}

// =================================================================================================

void test_3(benchmark::State & state) // note: fast
{
    auto vector = make_vector(state.range(0));

    for (auto _ : state)
    {
        std::for_each(std::execution::par_unseq, std::begin(vector), std::end(vector),

			[](auto & x) constexpr noexcept { x = std::sin(std::cos(x)); });
    }
}

// =================================================================================================

BENCHMARK(test_1)->DenseRange(1'000'000, 5'000'000, 1'000'000);
BENCHMARK(test_2)->DenseRange(1'000'000, 5'000'000, 1'000'000);
BENCHMARK(test_3)->DenseRange(1'000'000, 5'000'000, 1'000'000);

// =================================================================================================

int main(int argc, char ** argv) // note: arguments for benchmark
{
	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

    return 0;
}