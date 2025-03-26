#include <cassert>
#include <cmath>
#include <limits>
#include <string>

#include <boost/multiprecision/cpp_bin_float.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto equal(T x, T y, T epsilon = std::numeric_limits < T > ::epsilon())
{
	return boost::multiprecision::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    boost::multiprecision::cpp_bin_float_100 x("0." + std::string(100, '3'));

//  boost::multiprecision::cpp_bin_float_100 y(1.0 / 3); // bad

    boost::multiprecision::cpp_bin_float_100 z(1);

//  -------------------------------------------------------------------------
    
    z /= 3;

//  -------------------------------------------------------------------------

//  assert(equal(x, y) == 0); // bad

    assert(equal(x, z) == 1);
}