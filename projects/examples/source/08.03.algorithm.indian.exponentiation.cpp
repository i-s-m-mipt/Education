#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

#include <gtest/gtest.h>

//  ================================================================================================

[[nodiscard]] constexpr unsigned long long pow(unsigned long long base, unsigned long long exp)
{
    if (base == 0) return (exp == 0 ? 1 : 0);

    auto result = 1ull;

    while (exp > 0)
    {
        if (exp & 1)
        {
            if (result > std::numeric_limits < unsigned long long > ::max() / base)
            {
                throw std::runtime_error("arithmetic overflow");
            }

            result *= base;
        }

        if (exp /= 2; exp == 0) break;

        if (base > std::numeric_limits < unsigned long long > ::max() / base)
        {
            throw std::runtime_error("arithmetic overflow");
        }

        base *= base;
    }

    return result;
}

//  ================================================================================================

TEST(Algorithm, Indian_Exponentiation)
{
    ASSERT_EQ(pow(2,  0),          1);
    ASSERT_EQ(pow(2,  1),          2);
    ASSERT_EQ(pow(2,  2),          4);
    ASSERT_EQ(pow(2,  4),         16);
    ASSERT_EQ(pow(2,  8),        256);
    ASSERT_EQ(pow(2, 16),      65536);
    ASSERT_EQ(pow(2, 32), 4294967296);
}

//  ================================================================================================

int main(int argc, char ** argv)
{
	try
    {
        [[maybe_unused]] auto result = pow(2, 64);
    }
    catch (const std::exception & exception)
    {
        std::cerr << exception.what() << '\n';
    }

//  ================================================================================================

	testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}