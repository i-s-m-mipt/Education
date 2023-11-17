#include <cmath>
#include <cstdlib>
#include <iostream>

double f(std::size_t size) // note: complex calculations
{
	auto result = 0.0;

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			auto argument = 1.0 * i / size;

			auto l = std::pow(std::sin(argument), 2.0);
			auto r = std::pow(std::cos(argument), 2.0);

			result += (l + r); // note: required optimization
		}
	}

	return result;
}

int main()
{
	std::cout << f(1)     << std::endl;
	std::cout << f(10)    << std::endl;
	std::cout << f(100)   << std::endl;
	std::cout << f(1000)  << std::endl;
	std::cout << f(10000) << std::endl;

	return 0;
}