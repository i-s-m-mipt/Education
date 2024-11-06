#include <cassert>
#include <cerrno>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>

//  ================================================================================================

auto equal_v1(double x, double y)
{
	return std::abs(x - y) < std::numeric_limits < double > ::epsilon();
}

auto equal_v2(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

auto equal_v3(double x, double y, double scale)
{
	return std::abs(x - y) < std::max(std::abs(x), std::abs(y)) * scale;
}

auto equal_v4(double x, double y, double scale, double epsilon)
{
	return std::abs(x - y) < epsilon ? true : equal_v3(x, y, scale);
}

//  ================================================================================================

int main()
{
	std::cout << 1.67e-5 << std::endl;

	std::cout << std::fixed        << 3.14 << std::endl;
	std::cout << std::scientific   << 3.14 << std::endl;
	std::cout << std::defaultfloat << 3.14 << std::endl;

//  ================================================================================================

	auto precision = std::cout.precision();

	auto max_precision = std::numeric_limits < double > ::digits10 + 1;

	for (auto precision = 0; precision <= max_precision; ++precision)
	{
		std::cout << std::setw(2) << std::setfill(' ') << std::right << precision << " : ";
		
		std::cout << std::setprecision(precision) << std::fixed << std::numbers::pi << '\n';
	}

	std::cout << std::setprecision(precision);

//  ================================================================================================

	std::cout << std::numeric_limits < double > ::min() << std::endl;
	std::cout << std::numeric_limits < double > ::max() << std::endl;

	if (std::numeric_limits < double > ::has_infinity)
	{
		std::cout << std::numeric_limits < double > ::infinity() << std::endl;
	}

//  ================================================================================================

	std::cout << errno << ' ' << std::log(-1) << ' ' << errno << std::endl; // support: cerrno

	auto x = 0.0, y = 1.0;

	std::cout << -x / y << std::endl; // support: IEEE-754
}