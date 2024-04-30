#include <iterator>
#include <limits>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// =================================================================================================

[[nodiscard]] inline constexpr int factorial(int n) noexcept 
{ 
    return (n < 2 ? 1 : n * factorial(n - 1)); 
}

TEST(Factorial, Results) // note: group name and test case name
{
    EXPECT_EQ(factorial(0),     1);
    EXPECT_EQ(factorial(1),     1);
    EXPECT_EQ(factorial(2),     2);
    EXPECT_EQ(factorial(3),     6);
    EXPECT_EQ(factorial(5),   120);
    EXPECT_EQ(factorial(8), 40320);

    ASSERT_EQ(factorial(4),    25); // note: failed assertion
}

// =================================================================================================

[[nodiscard]] testing::AssertionResult is_even(int n) 
{
    return (n % 2 == 0 ? testing::AssertionSuccess() : 
                         testing::AssertionFailure() << n << " is odd");
}

TEST(Miscellaneous, Expectations) 
{ 
    EXPECT_TRUE(is_even(43)); // note: failed expectation

    EXPECT_THAT("Hello, world!", testing::StartsWith("Hello"));

    EXPECT_THAT("data.txt", testing::MatchesRegex("([a-z]+)\\.txt"));

    EXPECT_DOUBLE_EQ(3.14, 3.15) << "not equal doubles";

    EXPECT_NEAR(3.14, 3.14, std::numeric_limits < double > ::epsilon());
} 

// =================================================================================================

class Fixture : public testing::Test 
{
public:

    Fixture() noexcept {} // note:   setup actions
   ~Fixture() noexcept {} // note: cleanup actions

    void    SetUp() override { data.push_back(42); } // note: called after constructor
    void TearDown() override { data.clear      (); } // note: called before destructor

    std::vector < int > data;

}; // class Fixture : public testing::Test 

TEST_F(Fixture, Size) 
{
    ASSERT_EQ(std::size(data), 1); data.push_back(43);
    ASSERT_EQ(std::size(data), 2);
}

// =================================================================================================

class Parameters : public Fixture, public testing::WithParamInterface < int > {};

TEST_P(Parameters, Resize) { data.resize(GetParam(), 0); ASSERT_EQ(std::size(data), GetParam()); }

INSTANTIATE_TEST_CASE_P(Test, Parameters, testing::Values(0, 1, 2, 4, 8)); // note: testing::Range(0, 10)

// =================================================================================================

int main(int argc, char ** argv) // note: arguments for testing
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}