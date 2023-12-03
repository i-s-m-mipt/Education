#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

double calculate_pi()
{
	std::random_device device; // note: make seed only once

	std::mt19937 engine(device());

	std::uniform_real_distribution distribution(0.0, 1.0); // note: [a; b)

	const std::size_t size = 10'000'000; // note: try in release mode

	std::size_t counter = 0;

	for (std::size_t i = 0; i < size; ++i)
	{
		auto x = distribution(engine);
		auto y = distribution(engine);

		if (x * x + y * y < 1.0) ++counter;
	}

	return 4.0 * counter / size;
}

int main()
{
	std::random_device device; // note: implementation defined entropy source

	std::mt19937 engine(device());

	std::normal_distribution distribution(20.0, 5.0);

	std::vector < std::size_t > values(40, 0);

	for (std::size_t i = 0; i < 100'000; ++i)
	{
		if (auto value = distribution(engine); value > 0.0)
		{
			if (auto index = static_cast < std::size_t > (std::round(value)); index < values.size())
			{
				++values[index];
			}
		}
	}

	for (std::size_t i = 0; i < values.size(); ++i)
	{
		std::cout << std::setw(2) << std::right << std::setfill(' ') << i << " : ";

		std::cout << std::string(values[i] / 100, '*') << std::endl;
	}

	std::cout << "pi = " << calculate_pi() << std::endl; // note: monte-carlo method

	return 0;
}