#include <cmath>
#include <cstddef>
#include <format>
#include <iostream>
#include <random>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::random_device device;

	std::mt19937_64 engine(device());

	std::normal_distribution distribution(25.0, 8.0);

	std::vector < std::size_t > vector(50, 0);

	for (auto i = 0uz; i < 1'000'000; ++i)
	{
		if (auto x = distribution(engine); x > 0.0)
		{
			if (auto j = static_cast < std::size_t > (std::floor(x)); j < std::size(vector))
			{
				++vector[j];
			}
		}
	}

	for (auto i = 0uz; i < std::size(vector); ++i)
	{
		std::cout << "main : vector[" << std::format("{:0>2}", i) << "] : ";

		std::cout << std::string(vector[i] / 1'000, '+') << '\n';
	}
}