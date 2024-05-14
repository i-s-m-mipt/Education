#include <bitset>
#include <cmath>
#include <iomanip>
#include <iostream>

#include <gtest/gtest.h>

//  ================================================================================================

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

//  ================================================================================================

TEST(Algorithm, Binary_Gray_Code)
{
    constexpr std::size_t size = 5;

    for (unsigned int n = 0; n < static_cast < unsigned int > (std::pow(2, size)); ++n)
    {
        ASSERT_EQ(n, gray_decode(gray_encode(n)));
    }
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    constexpr std::size_t size = 5;

    using binary = std::bitset < size > ;

    for (unsigned int n = 0; n < static_cast < unsigned int > (std::pow(2, size)); ++n)
    {
        std::cout << std::setw(2) << std::right << std::setfill('0') << n << ' ';

        std::cout << binary(gray_encode(n)) << std::endl;
    }

//  ================================================================================================

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}