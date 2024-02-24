#include <gtest/gtest.h>

unsigned int factorial(unsigned int n)
{
	return (n < 2 ? 1 : n * factorial(n - 1));
}

TEST(factorial_test, zero) 
{
    EXPECT_EQ(factorial(0), 1);
}

TEST(factorial_test, positive) 
{
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(2), 2);
    EXPECT_EQ(factorial(3), 6);
    EXPECT_EQ(factorial(5), 120);
    EXPECT_EQ(factorial(8), 40320);
}

TEST(factorial_test, fail) 
{
    EXPECT_EQ(factorial(4), 25); // note: failed test
}

int main(int argc, char ** argv) // note: arguments for testing
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}