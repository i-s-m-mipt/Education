#include <cassert>
#include <cerrno>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

/////////////////////////////////////////////////////////////////////////////////////////

auto equal_v1(double x, double y)
{
	return std::abs(x - y) < std::numeric_limits < double > ::epsilon();
}

/////////////////////////////////////////////////////////////////////////////////////////

auto equal_v2(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////////////

auto equal_v3(double x, double y, double scale)
{
	return std::abs(x - y) < std::max(std::abs(x), std::abs(y)) * scale;
}

/////////////////////////////////////////////////////////////////////////////////////////

auto equal_v4(double x, double y, double epsilon, double scale)
{
	return std::abs(x - y) < epsilon ? true : equal_v3(x, y, scale);
}

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "0.000001 = " << std::scientific << std::defaultfloat << 1.0e-6 << '\n';

//  -------------------------------------------------------------------------------------

	auto precision = std::cout.precision();

	auto max_precision = std::numeric_limits < double > ::digits10;

	for (auto precision = 0; precision <= max_precision; ++precision)
	{
		std::cout << "precision = ";

		std::cout << std::setw(2) << std::setfill('0') << std::right << precision << ' ';

		std::cout << "d = ";
		
		std::cout << std::setprecision(precision) << std::fixed << 1.0 << '\n';
	}

	std::cout << std::setprecision(precision);

//  -------------------------------------------------------------------------------------

	if (std::numeric_limits < double > ::has_infinity)
	{
		std::cout << "std::numeric_limits < double > ::infinity() = ";

		std::cout <<  std::numeric_limits < double > ::infinity() << '\n';
	}

//  -------------------------------------------------------------------------------------

	std::cout << "std::log(-1) = " << std::log(-1) << '\n';
	
	std::cout << "main : " << std::strerror(errno) << '\n';

//  -------------------------------------------------------------------------------------

	assert( equal_v2(1.0, 1.000'001));
	
//	assert( equal_v2(1e-6, 1e-9)); // bad
	
//	assert(!equal_v2(1'000.0, 1'000.000'001)); // bad

	auto d = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;

    assert( equal_v3(d, 1.0, 1e-6));

//  assert(!equal_v3(d - 1.0, 0.0, 1e-6)); // bad

	assert( equal_v4(d - 1.0, 0.0, 1e-9, 1e-6));
}