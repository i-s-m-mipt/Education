#include <iterator>
#include <limits>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

//  ================================================================================================

[[nodiscard]] auto is_even(int x) 
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

//  ---------------------------------------------------------

TEST(Expect, Is_Even)
{
    EXPECT_TRUE(is_even(1));
    EXPECT_TRUE(is_even(2));
}

TEST(Assert, Is_Even)
{
    ASSERT_TRUE(is_even(1));
    ASSERT_TRUE(is_even(2));
}

//  ================================================================================================

TEST(Assert, Miscellaneous) 
{
    ASSERT_NEAR(1.0, 1.0, 1e-6);

    ASSERT_THAT("aaaaa", testing::StartsWith("a"));
}

//  ================================================================================================

struct Fixture : public testing::Test 
{
    Fixture() = default;
   ~Fixture() = default;

//  -------------------------

    std::vector < int > data;
};

//  -------------------------------------------------

TEST_F(Fixture, Data) 
{
    ASSERT_EQ(std::size(data), 0); data.push_back(1);
    ASSERT_EQ(std::size(data), 1); data.push_back(2);
    ASSERT_EQ(std::size(data), 2);
}

//  ================================================================================================

struct Parameters : public Fixture, public testing::WithParamInterface < int > {};

//  ------------------------------------------------------------------------------

TEST_P(Parameters, Size) 
{ 
    auto size = GetParam();

    data.resize(size, 0); 
    
    ASSERT_EQ(std::size(data), size); 
}

//  -------------------------------------------------------------------------

INSTANTIATE_TEST_CASE_P(Fixture, Parameters, testing::Values(1, 2, 3, 4, 5));

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}