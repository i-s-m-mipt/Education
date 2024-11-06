#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

#include <boost/multiprecision/cpp_int.hpp> // support: gmp_int

int main()
{
    std::cout << std::numeric_limits < boost::multiprecision::uint128_t > ::max() << std::endl;
    std::cout << std::numeric_limits < boost::multiprecision::uint256_t > ::max() << std::endl;
    std::cout << std::numeric_limits < boost::multiprecision::uint512_t > ::max() << std::endl;

//  ================================================================================================

    std::cout << boost::multiprecision::uint128_t(0) - 1 << std::endl;

    try
    {
        std::ignore = boost::multiprecision::checked_uint128_t(0) - 1;
    }
    catch (const std::range_error & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';
    }

//  ================================================================================================

    boost::multiprecision::cpp_int result = 1; 
    
    for (auto i = 1; i <= 100; ++i) 
    {
        result *= i; 
    }
   
    std::cout << "100! = " << result << '\n';
}