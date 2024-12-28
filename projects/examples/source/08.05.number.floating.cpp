#include <cassert>
#include <cerrno>
#include <cmath>
#include <cstring>
#include <format>
#include <iostream>
#include <limits>
#include <utility>

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
	std::cout << "main : 0.000001 = " << std::scientific << std::defaultfloat << 1.0e-6 << '\n';

//  -------------------------------------------------------------------------------------

	auto precision = std::cout.precision();

	auto max_precision = std::numeric_limits < double > ::digits10;

	for (auto precision = 0; precision <= max_precision; ++precision)
	{
		std::cout << "main : precision = " << std::format("{:0>2}", precision) << ' ';

		std::cout << "d = " << std::format("{:.{}f}", 1.0, precision) << '\n';
	}

	std::cout.precision(precision);

//  -------------------------------------------------------------------------------------

	if (std::numeric_limits < double > ::has_infinity)
	{
		auto infinity = std::numeric_limits < double > ::infinity();

		std::cout << "main : infinity = " << infinity << '\n';
	}

//  -------------------------------------------------------------------------------------

	if (std::numeric_limits < double > ::has_quiet_NaN)
	{
		auto quiet_NaN = std::numeric_limits < double > ::quiet_NaN();

		std::cout << "main : quiet_NaN = " << quiet_NaN << '\n';
	}

//  -------------------------------------------------------------------------------------

	if (std::numeric_limits < double > ::has_signaling_NaN)
	{
		auto signaling_NaN = std::numeric_limits < double > ::signaling_NaN();

		std::cout << "main : signaling_NaN = " << signaling_NaN << '\n';
	}

//  -------------------------------------------------------------------------------------

	std::ignore = std::log(-1);
	
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