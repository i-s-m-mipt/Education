#include <cassert>
#include <cmath>
#include <limits>

////////////////////////////////////////////////////////////////////////

auto equal_v1(double x, double y)
{
	return std::abs(x - y) < std::numeric_limits < double > ::epsilon();
}

////////////////////////////////////////////////////////////////////////

auto equal_v2(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

////////////////////////////////////////////////////////////////////////

auto equal_v3(double x, double y, double scale)
{
	return std::abs(x - y) < std::max(std::abs(x), std::abs(y)) * scale;
}

////////////////////////////////////////////////////////////////////////

auto equal_v4(double x, double y, double scale, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon ? true : equal_v3(x, y, scale);
}

////////////////////////////////////////////////////////////////////////

int main()
{
    assert( equal_v1(1.0, 1.0));

//  -------------------------------------------------------------------

	assert( equal_v2(1.0, 1.000'001));
	
//	assert( equal_v2(1e-6, 1e-9)); // bad
	
//	assert(!equal_v2(1'000.0, 1'000.001)); // bad

//  -------------------------------------------------------------------

	assert(!equal_v3(1e-6, 1e-9, 1e-6));

	assert( equal_v3(1'000.0, 1'000.001, 1e-6));

//  -------------------------------------------------------------------

	auto x = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;

//  -------------------------------------------------------------------

    assert( equal_v3(x, 1.0, 1e-6));

// 	assert(!equal_v3(x - 1.0, 0.0, 1e-6)); // bad

//  -------------------------------------------------------------------

	assert( equal_v4(x - 1.0, 0.0, 1e-6));
}