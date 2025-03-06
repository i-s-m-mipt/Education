#include <iterator>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

//////////////////////////////////////////////////////////////////////////////

TEST(Expect, Test)
{
    std::cout << "Test::Expect::Test (1)\n"; EXPECT_TRUE(std::max(1, 2) == 1);

    std::cout << "Test::Expect::Test (2)\n"; EXPECT_TRUE(std::max(1, 2) == 2);
}

//////////////////////////////////////////////////////////////////////////////

TEST(Assert, Test)
{
    std::cout << "Test::Assert::Test (1)\n"; ASSERT_TRUE(std::max(1, 2) == 1);

    std::cout << "Test::Assert::Test (2)\n"; ASSERT_TRUE(std::max(1, 2) == 2);
}

//////////////////////////////////////////////////////////////////////////////

TEST(Assert, Near) 
{
    ASSERT_NEAR(1e-9, 2e-9, 1e-6);
}

//////////////////////////////////////////////////////////////////////////////

TEST(Assert, That)
{
    ASSERT_THAT("aaaaa", testing::StartsWith("aaa"));
}

//////////////////////////////////////////////////////////////////////////////

class Fixture : public testing::Test 
{
public:

    std::vector < int > data;
};

//////////////////////////////////////////////////////////////////////////////

TEST_F(Fixture, Data) 
{
    data.push_back(1); ASSERT_EQ(std::size(data), 1); 
    
    data.push_back(1); ASSERT_EQ(std::size(data), 2); 
}

//////////////////////////////////////////////////////////////////////////////

class Adapter : public Fixture, public testing::WithParamInterface < int > {};

//////////////////////////////////////////////////////////////////////////////

TEST_P(Adapter, Data) 
{ 
    auto x = GetParam();
    
    data.resize(x, 0);
    
    ASSERT_EQ(std::size(data), x);
}

//////////////////////////////////////////////////////////////////////////////

INSTANTIATE_TEST_CASE_P(Fixture, Adapter, testing::Values(1, 2, 3, 4, 5));

//////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

//  -------------------------------------
    
    return RUN_ALL_TESTS();
}