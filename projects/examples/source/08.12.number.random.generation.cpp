#include <cassert>
#include <cmath>
#include <cstddef>
#include <format>
#include <iostream>
#include <random>
#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::random_device device;

		std::mt19937_64 engine(device());

		std::normal_distribution distribution(25.0, 8.0);

		std::vector < std::size_t > numbers(50, 0);

		for (auto i = 0uz; i < 1'000'000; ++i)
		{
			if (auto number = distribution(engine); number > 0.0)
			{
				auto index = static_cast < std::size_t > (std::floor(number));

				if (index < std::size(numbers)) 
				{
					++numbers[index];
				}
			}
		}

		for (auto i = 0uz; i < std::size(numbers); ++i)
		{
			std::cout << "main : numbers[" << std::format("{:0>2}", i) << "] : ";

			std::cout << std::string(numbers[i] / 1'000, '+') << '\n';
		}
	}

//  -----------------------------------------------------------------------------

	{
		auto size = 100'000'000uz;

		std::default_random_engine engine;

		std::uniform_real_distribution distribution(0.0, 1.0);

		auto counter = 0uz;

		for (auto i = 0uz; i < size; ++i)
		{
			auto x = distribution(engine), y = distribution(engine);

			if (x * x + y * y < 1.0) 
			{
				++counter;
			}
		}

		assert(equal(4.0 * counter / size, 3.141, 1e-3));
	}	
}