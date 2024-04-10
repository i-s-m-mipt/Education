#include <iomanip>
#include <iostream>
#include <numbers>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp> // note: gmp_float is ~2 times faster

template < typename T > [[nodiscard]] inline constexpr T area(T r) noexcept
{
	return boost::math::constants::pi < T > () * r * r; // note: remember variable templates
}

int main()
{
    using float_100 = boost::multiprecision::cpp_bin_float_100; // note: consider cpp_dec_float_100 also

    constexpr auto precision = std::numeric_limits < float_100 > ::digits10;

    std::cout << std::setprecision(precision) << float_100(3.14) << std::endl;

    float_100 b = 2.0; 

    std::cout << std::setprecision(precision) << boost::multiprecision::log(b) << std::endl;

    std::cout << std::setprecision(precision) << float_100(1.0  / 7.0) << std::endl;
    std::cout << std::setprecision(precision) << float_100(1.0) / 7.0  << std::endl; // good: big float

    std::cout << boost::math::tgamma(float_100(1000)) << std::endl;

    std::cout << std::setprecision(std::numeric_limits < float  > ::digits10) << area(1.0f) << std::endl;
    std::cout << std::setprecision(std::numeric_limits < double > ::digits10) << area(1.0 ) << std::endl;

    std::cout << std::setprecision(precision) << area(float_100(1.0)) << std::endl;

    return 0;
}