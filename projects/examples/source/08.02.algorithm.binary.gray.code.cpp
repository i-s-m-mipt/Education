#include <bitset>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>

//  ================================================================================================

[[nodiscard]] auto encode(unsigned int x)
{
    return x ^ (x >> 1);
}

[[nodiscard]] auto decode(unsigned int code)
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

//  ================================================================================================

int main()
{
    std::cout << '\n';

    for (unsigned int n = 0; n < static_cast < unsigned int > (std::pow(2, 5)); ++n)
    {
        std::cout << "n = " << std::setw(2) << std::setfill('0') << std::right << n << ' ';

        std::cout << "code = " << std::bitset < 5 > (encode(n)) << '\n';

        assert(decode(encode(n)) == n);
    }

    std::cout << '\n';
}