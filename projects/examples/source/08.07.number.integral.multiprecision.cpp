#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

#include <boost/multiprecision/cpp_int.hpp>

//////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        auto x = std::numeric_limits < boost::multiprecision::uint128_t > ::max();

        assert(boost::multiprecision::uint128_t(0) - 1 == x);
    }

//  ------------------------------------------------------------------------------

    {
        try
        {
            std::ignore = boost::multiprecision::checked_uint128_t(0) - 1;
        }
        catch (const std::range_error & exception)
        {
            std::cerr << "main : " << exception.what() << '\n';
        }
    }

//  ------------------------------------------------------------------------------

    {
        boost::multiprecision::cpp_int x = 1;
    
        for (auto i = 1; i <= 100; ++i) 
        {
            x *= i;
        }
    
        std::cout << "main : x = " << x << '\n';
    }
}