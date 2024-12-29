#include <cassert>
#include <cerrno>
#include <cmath>
#include <cstring>
#include <format>
#include <iostream>
#include <limits>
#include <utility>

/////////////////////////////////////////////////////////////////////////////////////////////////

auto equal_v1(double x, double y)
{
	return std::abs(x - y) < std::numeric_limits < double > ::epsilon();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

auto equal_v2(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

auto equal_v3(double x, double y, double scale)
{
	return std::abs(x - y) < std::max(std::abs(x), std::abs(y)) * scale;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

auto equal_v4(double x, double y, double scale, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon ? true : equal_v3(x, y, scale);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	assert(std::format("{:.1e}", 1.0e-6) == "1.0e-06");

//  ---------------------------------------------------------------------------------------------

	for (auto precision = 1; precision <= std::numeric_limits < double > ::digits10; ++precision)
	{
		assert(std::format("{:.{}f}", 1.0, precision) == "1." + std::string(precision, '0'));
	}

//  ---------------------------------------------------------------------------------------------

	if (std::numeric_limits < double > ::has_infinity )
	{
		assert(std::format("{}", std::numeric_limits < double > ::infinity ()) == "inf");
	}

	if (std::numeric_limits < double > ::has_quiet_NaN)
	{
		assert(std::format("{}", std::numeric_limits < double > ::quiet_NaN()) == "nan");
	}

//  ---------------------------------------------------------------------------------------------

	assert(errno == 0); std::ignore = std::log(-1); assert(errno != 0);
	
	std::cout << "main : " << std::strerror(errno) << '\n';

//  ---------------------------------------------------------------------------------------------

	assert( equal_v1(1.0, 1.0));

	assert( equal_v2(1.0, 1.000'001));
	
//	assert( equal_v2(1e-6, 1e-9)); // bad
	
//	assert(!equal_v2(1'000.0, 1'000.001)); // bad

	assert(!equal_v3(1e-6, 1e-9, 1e-6));

	assert( equal_v3(1'000.0, 1'000.001, 1e-6));

	auto d = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;

    assert( equal_v3(d, 1.0, 1e-6));

// 	assert(!equal_v3(d - 1.0, 0.0, 1e-6)); // bad

	assert( equal_v4(d - 1.0, 0.0, 1e-6));
}