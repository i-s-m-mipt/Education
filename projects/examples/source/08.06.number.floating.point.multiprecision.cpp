#include <iomanip>
#include <iostream>
#include <numbers>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp> // support: gmp_float

//  ================================================================================================

template < typename T > [[nodiscard]] inline constexpr T area(T radius) noexcept
{
	return boost::math::constants::pi < T > () * radius * radius;
}

//  ================================================================================================

int main()
{
    using float_100 = boost::multiprecision::cpp_bin_float_100;

    constexpr auto precision = std::numeric_limits < float_100 > ::digits10;

    std::cout << std::setprecision(precision) << std::fixed;

    std::cout << float_100(3.14      ) << std::endl;
    std::cout << float_100(1.0  / 3.0) << std::endl;
    std::cout << float_100(1.0) / 3.0  << std::endl;

//  ================================================================================================

    float_100 f = 2.0; 

    std::cout << boost::multiprecision::log(f) << std::endl;

    std::cout << boost::math::tgamma(float_100(1000)) << std::endl;

//  ================================================================================================

    std::cout << area(          1.0f) << std::endl;
    std::cout << area(          1.0 ) << std::endl;
    std::cout << area(float_100(1.0)) << std::endl;

    return 0;
}