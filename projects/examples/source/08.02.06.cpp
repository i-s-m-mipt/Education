#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <tuple>

#include <boost/multiprecision/cpp_int.hpp>

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(std::numeric_limits < boost::multiprecision::uint128_t > ::digits10 == 38);

//  ----------------------------------------------------------------------------------  

    boost::multiprecision::cpp_int x(std::string(32, '1'));

//  ----------------------------------------------------------------------------------  

    try
    {
        std::ignore = boost::multiprecision::checked_uint128_t(0) - 1;
    }
    catch (const std::range_error & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';
    }

//  ----------------------------------------------------------------------------------

    assert(std::numeric_limits < boost::multiprecision::uint128_t > ::max() + 1 == 0);
}