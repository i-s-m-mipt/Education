//////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <type_traits>

//////////////////////////////////////////////////////////////////////////////////////

template < typename T > T max_v1(T x, T y)
{
	return x < y ? y : x;
}

//////////////////////////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > T1 max_v2(T1 x, T2 y) 
{
	return x < y ? y : x;
}

//////////////////////////////////////////////////////////////////////////////////////

template < typename T1, typename T2, typename T3 > T3 max_v3(T1 x, T2 y)
{
	return x < y ? y : x;
}

//////////////////////////////////////////////////////////////////////////////////////

template < typename T3, typename T1, typename T2 > T3 max_v4(T1 x, T2 y)
{
	return x < y ? y : x;
}

//////////////////////////////////////////////////////////////////////////////////////

template < typename T3 = double, typename T1, typename T2 > T3 max_v5(T1 x, T2 y)
{
	return x < y ? y : x;
}

//////////////////////////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > std::common_type_t < T1, T2 > max_v6(T1 x, T2 y)
{
	return x < y ? y : x;
}

//////////////////////////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > auto max_v7(T1 x, T2 y)
{
	return x < y ? y : x;
}

//////////////////////////////////////////////////////////////////////////////////////

auto max_v8(auto x, auto y)
{
	return x < y ? y : x;
}

//////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(equal(max_v1(1,   2  ), 2)); // support : cppinsights.io

	assert(equal(max_v1(1.0, 2.0), 2)); // support : cppinsights.io
 
//	assert(equal(max_v1(1,   2.0), 2)); // error

//  ---------------------------------------------------------------

	assert(equal(max_v1(static_cast < double > (1), 2.0), 2));

//  ---------------------------------------------------------------

	assert(equal(max_v1 < double > (1, 2.0), 2));

//  ---------------------------------------------------------------

	assert(equal(max_v2(1.0, 2  ), 2));

//	assert(equal(max_v2(1,   2.0), 2)); // error

//  ---------------------------------------------------------------

	assert(equal(max_v3 < int, double, double > (1, 2.0), 2));

//  ---------------------------------------------------------------

	assert(equal(max_v4 < double > (1, 2.0), 2));

//  ---------------------------------------------------------------

	assert(equal(max_v5(1, 2.0), 2));
		
	assert(equal(max_v6(1, 2.0), 2));

	assert(equal(max_v7(1, 2.0), 2));

	assert(equal(max_v8(1, 2.0), 2)); // support : cppinsights.io

//  ---------------------------------------------------------------

	assert(equal(std::max(1.0, 2.0), 2));
	
//	assert(equal(std::max(1,   2.0), 2)); // error
}

//////////////////////////////////////////////////////////////////////////////////////