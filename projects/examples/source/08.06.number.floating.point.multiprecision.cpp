#include <iomanip>
#include <iostream>
#include <numbers>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp> // note: gmp_float is ~2 times faster

template < typename T > [[nodiscard]] inline constexpr T area(T radius) noexcept
{
	return boost::math::constants::pi < T > () * radius * radius; // note: remember variable templates
}

int main()
{
    using float_100 = boost::multiprecision::cpp_bin_float_100; // note: consider cpp_dec_float_100 also

    constexpr auto precision = std::numeric_limits < float_100 > ::digits10;

    std::cout << std::setprecision(precision) << std::fixed << float_100(3.14      ) << std::endl;
    std::cout << std::setprecision(precision) << std::fixed << float_100(1.0  / 3.0) << std::endl;
    std::cout << std::setprecision(precision) << std::fixed << float_100(1.0) / 3.0  << std::endl; // good: big float

//  ================================================================================================

    float_100 f = 2.0; 

    std::cout << std::setprecision(precision) << std::fixed << boost::multiprecision::log(f) << std::endl;

    std::cout << boost::math::tgamma(float_100(1000)) << std::endl;

//  ================================================================================================

    std::cout << std::setprecision(std::numeric_limits < float  > ::digits10) << std::fixed << area(1.0f) << std::endl;
    std::cout << std::setprecision(std::numeric_limits < double > ::digits10) << std::fixed << area(1.0 ) << std::endl;

    std::cout << std::setprecision(precision) << std::fixed << area(float_100(1.0)) << std::endl;

    return 0;
}