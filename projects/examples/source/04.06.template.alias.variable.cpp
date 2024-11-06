#include <cassert>
#include <cmath>
#include <numbers>

//  ================================================================================================

template < typename T, std::size_t S > class Array {};

template < typename T > using Buffer = Array < T, 1024 > ;

//  ================================================================================================

template < typename T > T pi = T(3.141592653589793238462643383279502884L);

template < typename T > [[nodiscard]] auto area(T radius)
{
	return pi < T > * radius * radius;
}

//  ================================================================================================

[[nodiscard]] auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//  ================================================================================================

int main()
{
	[[maybe_unused]] Buffer < int > buffer;

//  ------------------------------------------------------------------------------------------------

	assert(area(1) == 3);

	assert(equal(pi < double > , area(1.0)));

	assert(equal(pi < double > , std::numbers::pi));
}