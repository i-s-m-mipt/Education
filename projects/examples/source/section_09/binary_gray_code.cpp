#include <bitset>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>

[[nodiscard]] unsigned int gray_encode(unsigned int n) noexcept
{
    return n ^ (n >> 1);
}

[[nodiscard]] unsigned int gray_decode(unsigned int code) noexcept
{
    for (unsigned int bit = 1 << 31; bit > 1; bit >>= 1)
    {
        if (code & bit) code ^= bit >> 1;
    }

    return code;
}

int main()
{
    const std::size_t size = 4;

    using binary = std::bitset < size > ;

    for (unsigned int n = 0; n < static_cast < unsigned int > (std::pow(2, size)); ++n)
    {
        auto x = gray_encode(n);
        auto y = gray_decode(x);

        assert(n == y);

        std::cout << std::setw(2) << std::right << std::setfill('0') << n << ' ' << binary(x) << std::endl;
    }

    return 0;
}