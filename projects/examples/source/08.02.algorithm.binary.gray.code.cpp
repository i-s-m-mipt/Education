#include <bitset>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////

auto encode(unsigned int x)
{
    return x ^ (x >> 1);
}

///////////////////////////////////////////////////////////////////////////////////////////

auto decode(unsigned int code)
{
    for (auto bit = 1u << 31; bit > 1; bit >>= 1)
    {
        if (code & bit) 
        {
            code ^= bit >> 1;
        }
    }

    return code;
}

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    constexpr auto size = 4uz;

//  ---------------------------------------------------------------------------------------

    for (unsigned int x = 0; x < static_cast < unsigned int > (std::pow(2, size)); ++x)
    {
        std::cout << "x = " << std::setw(2) << std::setfill('0') << std::right << x << ' ';

        auto code = encode(x);

        std::cout << "code = " << std::bitset < size > (code) << '\n';

        assert(decode(code) == x);
    }
}