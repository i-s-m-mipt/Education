#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

[[nodiscard]] double calculate_pi() noexcept
{
	std::random_device device; // note: make seed only once

	std::mt19937_64 engine(device());

	std::uniform_real_distribution distribution(0.0, 1.0); // note: [a; b)

	constexpr std::size_t size = 1'000'000; // note: try in release mode

	std::size_t counter = 0;

	for (std::size_t i = 0; i < size; ++i)
	{
		const auto x = distribution(engine);
		const auto y = distribution(engine);

		if (x * x + y * y < 1.0) ++counter;
	}

	return 4.0 * counter / size;
}

int main()
{
	std::random_device device; // note: implementation defined entropy source

	std::mt19937_64 engine(device()); // note: engines use entropy sources for seeding

	std::normal_distribution distribution(20.0, 5.0); // note: distributions use engines

	std::vector < std::size_t > values(40, 0);

	constexpr std::size_t size = 1'000'000;

	for (std::size_t i = 0; i < size; ++i)
	{
		if (const auto value = distribution(engine); value > 0.0)
		{
			if (const auto index = static_cast < std::size_t > (std::floor(value)); index < std::size(values))
			{
				++values[index];
			}
		}
	}

	for (std::size_t i = 0; i < std::size(values); ++i)
	{
		std::cout << std::setw(2) << std::right << std::setfill(' ') << i << " : ";

		std::cout << std::string(values[i] / 1'000, '*') << std::endl;
	}

//  ================================================================================================

	std::cout << "pi = " << calculate_pi() << std::endl; // note: monte-carlo method

	return 0;
}