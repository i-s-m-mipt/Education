#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////

using float_100_t = boost::multiprecision::cpp_bin_float_100;

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename F > auto derivative(F && f, float_100_t x, float_100_t dx = 1e-9)
{
    auto d1 = f(x + 1 * dx) - f(x - 1 * dx);
    auto d2 = f(x + 2 * dx) - f(x - 2 * dx);
    auto d3 = f(x + 3 * dx) - f(x - 3 * dx);

    return (15 * d1 / 2 - 6 * d2 / 4 + 1 * d3 / 6) / (10 * dx);
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto equal(T x, T y, T epsilon = std::numeric_limits < T > ::epsilon())
{
	return boost::multiprecision::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto max_precision = std::numeric_limits < float_100_t > ::digits10;

//  ---------------------------------------------------------------------------------

    auto x = float_100_t("0." + std::string(max_precision, '3'));

    auto y = float_100_t(1.0) / 3.0;

    assert(equal(x, y));

    auto z = boost::math::constants::pi < float_100_t > () / 2;

//  ---------------------------------------------------------------------------------

    auto d_sin = derivative
    (
        [](const auto & x){ return boost::multiprecision::sin(x); }, z
    );

    assert(equal < float_100_t > (d_sin, 0.0));

//  ---------------------------------------------------------------------------------

    auto d_gamma_p_1 = derivative
    (
        [](const auto & x){ return boost::math::gamma_p(2.0, x); }, z
    );

    std::cout << std::setprecision(max_precision) << std::fixed;

    std::cout << "d_gamma_p_1 = " << d_gamma_p_1 << '\n';

    std::cout << "d_gamma_p_2 = " << boost::math::gamma_p_derivative(2.0, z) << '\n';
}