#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

#include <boost/multiprecision/cpp_int.hpp> // note: gmp_int is ~10 times faster

int main()
{
    std::cout << std::numeric_limits < boost::multiprecision::uint128_t > ::max() << std::endl;
    std::cout << std::numeric_limits < boost::multiprecision::uint256_t > ::max() << std::endl;
    std::cout << std::numeric_limits < boost::multiprecision::uint512_t > ::max() << std::endl;

    std::cout << boost::multiprecision::uint128_t(0) - 1 << std::endl; // note: outputs same as max()

    try
    {
        std::cout << boost::multiprecision::checked_uint128_t(0) - 1 << std::endl;
    }
    catch (const std::exception & exception)
    {
        std::cerr << exception.what() << '\n';
    }

    boost::multiprecision::cpp_int result = 1; for (auto i = 1; i < 101; ++i) result *= i; 
   
    std::cout << result << std::endl; // note: outputs 100!

    return 0;
}