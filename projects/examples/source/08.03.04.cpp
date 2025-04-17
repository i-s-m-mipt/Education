///////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <limits>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename F, typename T > auto derivative(F && f, T x, T dx = 1e-9)
{
    auto a = f(x + 1 * dx) - f(x - 1 * dx);

    auto b = f(x + 2 * dx) - f(x - 2 * dx);

    auto c = f(x + 3 * dx) - f(x - 3 * dx);

//  --------------------------------------------------------

    return (15 * a / 2 - 6 * b / 4 + 1 * c / 6) / (10 * dx);
}

///////////////////////////////////////////////////////////////////////////////////////////////

auto test_v1(boost::multiprecision::cpp_bin_float_100 const & x)
{
    return boost::multiprecision::sin(x);
}

///////////////////////////////////////////////////////////////////////////////////////////////

auto test_v2(boost::multiprecision::cpp_bin_float_100 const & x)
{
    return boost::math::gamma_p(2.0, x);
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto equal(T x, T y, T epsilon = std::numeric_limits < T > ::epsilon())
{
	return boost::multiprecision::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    using float_100_t = boost::multiprecision::cpp_bin_float_100;

//  ----------------------------------------------------------------------------------------

    float_100_t x = boost::math::constants::pi < float_100_t > () / 2;

    float_100_t y = 0;

    float_100_t z = boost::math::gamma_p_derivative(2.0, x);

//  ----------------------------------------------------------------------------------------

    float_100_t epsilon("0." + std::string(55, '0') + '1');

//  ----------------------------------------------------------------------------------------

    assert(equal(derivative(test_v1, x), y));

    assert(equal(derivative(test_v2, x), z, epsilon));
}

///////////////////////////////////////////////////////////////////////////////////////////////