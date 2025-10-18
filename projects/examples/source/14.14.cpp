///////////////////////////////////////////////////////////////////////////////////////////////

// support : en.wikipedia.org/wiki/Amdahl%27s_law

///////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <execution>
#include <iterator>
#include <random>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////////

auto make_vector(std::size_t size)
{
	std::vector < double > vector(size, 0);

    std::uniform_real_distribution distribution(0.0, 1.0);

	std::default_random_engine engine;

    auto lambda = [&engine, &distribution](){ return distribution(engine); };

	std::ranges::generate(vector, lambda);

	return vector;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void calculate(double & x)
{
    x = std::pow(std::sin(x), 2) + std::pow(std::cos(x), 2);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto vector = make_vector(1'000'000);

    auto begin = std::begin(vector), end = std::end(vector);

    for (auto element : state)
    {
        switch (state.range(0))
        {
            case 1: { std::for_each(std::execution::seq,       begin, end, calculate); break; }

            case 2: { std::for_each(std::execution::    unseq, begin, end, calculate); break; }

            case 3: { std::for_each(std::execution::par,       begin, end, calculate); break; }

            case 4: { std::for_each(std::execution::par_unseq, begin, end, calculate); break; }
        }

        benchmark::DoNotOptimize(vector);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2)->Arg(3)->Arg(4);

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////////////////