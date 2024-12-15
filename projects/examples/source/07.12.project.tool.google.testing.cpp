#include <iterator>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

/////////////////////////////////////////////////////////////////////////////////

auto is_even(int x) 
{
    if (x % 2 == 0)
    {
        return testing::AssertionSuccess();
    }
    else
    {
        return testing::AssertionFailure() << x << " is odd";
    }
}

/////////////////////////////////////////////////////////////////////////////////

TEST(Expect, Is_Even)
{
    EXPECT_TRUE(is_even(1)); std::cout << "Test::Expect::Is_Even (1)\n";
    EXPECT_TRUE(is_even(2)); std::cout << "Test::Expect::Is_Even (2)\n";
}

TEST(Assert, Is_Even)
{
    ASSERT_TRUE(is_even(1)); std::cout << "Test::Assert::Is_Even (1)\n";
    ASSERT_TRUE(is_even(2)); std::cout << "Test::Assert::Is_Even (2)\n";
}

/////////////////////////////////////////////////////////////////////////////////

TEST(Assert, Miscellaneous) 
{
    ASSERT_NEAR(1.0, 1.0, 1e-6);

    ASSERT_THAT("aaaaa", testing::StartsWith("a"));
}

/////////////////////////////////////////////////////////////////////////////////

class Fixture : public testing::Test 
{
public:

    std::vector < int > data;
};

TEST_F(Fixture, Data) 
{
    ASSERT_EQ(std::size(data), 0); data.push_back(1);
    ASSERT_EQ(std::size(data), 1); data.push_back(2);
    ASSERT_EQ(std::size(data), 2); 
}

/////////////////////////////////////////////////////////////////////////////////

class Parameters : public Fixture, public testing::WithParamInterface < int > {};

TEST_P(Parameters, Data) 
{ 
    auto value = GetParam();

    data.push_back(value); 
    
    ASSERT_EQ(data.back(), value); 
}

INSTANTIATE_TEST_CASE_P(Fixture, Parameters, testing::Values(1, 2, 3, 4, 5));

/////////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}