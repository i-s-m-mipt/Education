#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main()
{
	std::random_device device;

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
		std::cout << std::string(values[i] / 100, '*') << std::endl;
	}

	return 0;
}