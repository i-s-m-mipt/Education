#include <cassert>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

//  ================================================================================================

auto evaluate(std::size_t size)
{
	std::random_device device;

	std::mt19937_64 engine(device());

	std::uniform_real_distribution distribution(0.0, 1.0);

	auto counter = 0uz;

	for (auto i = 0uz; i < size; ++i)
	{
		auto x = distribution(engine);
		auto y = distribution(engine);

		if (x * x + y * y < 1.0) 
		{
			++counter;
		}
	}

	return 4.0 * counter / size;
}

//  ================================================================================================

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//  ================================================================================================

int main()
{
	std::random_device device;

	std::mt19937_64 engine(device());

	std::normal_distribution distribution(20.0, 5.0);

	std::vector < std::size_t > values(40, 0);

	for (auto i = 0uz; i < 1'000'000; ++i)
	{
		if (auto value = distribution(engine); value > 0.0)
		{
			auto index = static_cast < std::size_t > (std::floor(value));

			if (index < std::size(values)) 
			{
				++values[index];
			}
		}
	}

	for (auto i = 0uz; i < std::size(values); ++i)
	{
		std::cout << std::setw(2) << std::setfill(' ') << std::right << i << " : ";

		std::cout << std::string(values[i] / 1000, '*') << std::endl;
	}

//  ================================================================================================

	assert(equal(evaluate(100'000'000), 3.141, 1e-3));
}