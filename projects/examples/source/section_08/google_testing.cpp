#include <iterator>
#include <vector>

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
    ASSERT_EQ(factorial(4), 25); // note: failed test
}

class Test_Fixture : public testing::Test 
{
protected:

     Test_Fixture() noexcept {} // note:   setup actions
    ~Test_Fixture() noexcept {} // note: cleanup actions

    void SetUp   () override // note: called  after constructor
    {
        data.push_back(42);
    }

    void TearDown() override // note: called before  destructor
    {
        data.clear();
    } 

    std::vector < int > data;

}; // class Test_Fixture : public testing::Test 

TEST_F(Test_Fixture, test) 
{
    ASSERT_EQ(std::size(data), 1);

    data.push_back(43);

    ASSERT_EQ(std::size(data), 2);
}

int main(int argc, char ** argv) // note: arguments for testing
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}