#include <iomanip>
#include <iostream>
#include <limits>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp> // support: gmp_float

//  ================================================================================================

template < typename T > auto area(T radius)
{
	return boost::math::constants::pi < T > () * radius * radius;
}

//  ================================================================================================

int main()
{
    using float_100 = boost::multiprecision::cpp_bin_float_100;

    auto max_precision = std::numeric_limits < float_100 > ::digits10;

    std::cout << std::setprecision(max_precision) << std::fixed;

    std::cout << float_100(3.14      ) << std::endl;
    std::cout << float_100(1.0  / 3.0) << std::endl;
    std::cout << float_100(1.0) / 3.0  << std::endl;

//  ================================================================================================

    float_100 f = 2.0; 

    std::cout << boost::multiprecision::log(f) << std::endl;

    std::cout << boost::math::tgamma(float_100(1'000)) << std::endl;

//  ================================================================================================

    std::cout << area(          1.0f) << std::endl;
    std::cout << area(          1.0 ) << std::endl;
    std::cout << area(float_100(1.0)) << std::endl;
}