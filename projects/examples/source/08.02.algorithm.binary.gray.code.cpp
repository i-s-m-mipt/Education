#include <bitset>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>

[[nodiscard]] inline constexpr unsigned int gray_encode(unsigned int n) noexcept
{
    return n ^ (n >> 1);
}

[[nodiscard]] inline constexpr unsigned int gray_decode(unsigned int code) noexcept
{
    for (unsigned int bit = 1 << 31; bit > 1; bit >>= 1)
    {
        if (code & bit) code ^= bit >> 1;
    }

    return code;
}

int main()
{
    constexpr std::size_t size = 5;

    using binary = std::bitset < size > ;

    for (unsigned int n = 0; n < static_cast < unsigned int > (std::pow(2, size)); ++n)
    {
        const auto x = gray_encode(n);
        const auto y = gray_decode(x);

        assert(n == y);

        std::cout << std::setw(2) << std::right << std::setfill('0') << n << ' ' << binary(x) << std::endl;
    }

    return 0;
}