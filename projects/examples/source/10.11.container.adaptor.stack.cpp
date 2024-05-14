#include <cmath>
#include <iterator>
#include <stack>
#include <utility>

#include <gtest/gtest.h>

//  ================================================================================================

template < typename T > class Stack_v1 // complexity: T ~ O(1), S ~ O(N)
{
public:

    constexpr void push(T value)
    {
        const auto new_min = (std::empty(m_stack) ? value : std::min(value, m_stack.top().second));

        m_stack.emplace(value, new_min);
    }

    [[nodiscard]] constexpr T top() const noexcept { return m_stack.top().first; }
 
    constexpr void pop() noexcept { m_stack.pop(); }
 
    [[nodiscard]] constexpr std::size_t size() const noexcept { return m_stack.size(); }
 
    [[nodiscard]] constexpr T min() const noexcept { return m_stack.top().second; }

private:

    std::stack < std::pair < T, T > > m_stack;

}; // template < typename T > class Stack_v1

//  ================================================================================================

template < typename T > class Stack_v2 // complexity: T ~ O(1), S ~ O(1)
{
public:

    constexpr void push(T value)
    {
        if (std::empty(m_stack)) 
        {
            m_stack.push(value); m_min = m_stack.top();
        }
        else if (value < m_min) 
        {
            m_stack.push(2 * value - m_min); m_min = value;
        }
        else 
        {
            m_stack.push(value);
        }
    }

    [[nodiscard]] constexpr T top() const noexcept
    {
        return (m_stack.top() < m_min ? m_min : m_stack.top());
    }

    constexpr void pop() noexcept
    {
        if (auto t = m_stack.top(); t < m_min) 
        {
            (m_min *= 2) -= t;
        }

        m_stack.pop();
    }

    [[nodiscard]] constexpr std::size_t size() const noexcept { return m_stack.size(); }
 
    [[nodiscard]] constexpr T min() const noexcept { return m_min; }
 
private:

    std::stack < T > m_stack; 
    
    T m_min;

}; // template < typename T > requires std::is_arithmetic_v < T > class Stack_v2 

//  ================================================================================================

TEST(Stack_v1, Functions)
{
    Stack_v1 < int > stack_v1;

    stack_v1.push(3); ASSERT_EQ(stack_v1.top(), 3); ASSERT_EQ(stack_v1.min(), 3);
    stack_v1.push(5); ASSERT_EQ(stack_v1.top(), 5); ASSERT_EQ(stack_v1.min(), 3);
    stack_v1.push(2); ASSERT_EQ(stack_v1.top(), 2); ASSERT_EQ(stack_v1.min(), 2);
    stack_v1.push(1); ASSERT_EQ(stack_v1.top(), 1); ASSERT_EQ(stack_v1.min(), 1);
    stack_v1.push(1); ASSERT_EQ(stack_v1.top(), 1); ASSERT_EQ(stack_v1.min(), 1);

//  ================================================================================================

    stack_v1.pop  (); ASSERT_EQ(stack_v1.top(), 1); ASSERT_EQ(stack_v1.min(), 1);
    stack_v1.pop  (); ASSERT_EQ(stack_v1.top(), 2); ASSERT_EQ(stack_v1.min(), 2);
    stack_v1.pop  (); ASSERT_EQ(stack_v1.top(), 5); ASSERT_EQ(stack_v1.min(), 3);
    stack_v1.pop  (); ASSERT_EQ(stack_v1.top(), 3); ASSERT_EQ(stack_v1.min(), 3);
}

//  ================================================================================================

TEST(Stack_v2, Functions)
{
    Stack_v2 < int > stack_v2;
   
    stack_v2.push(3); ASSERT_EQ(stack_v2.top(), 3); ASSERT_EQ(stack_v2.min(), 3);
    stack_v2.push(5); ASSERT_EQ(stack_v2.top(), 5); ASSERT_EQ(stack_v2.min(), 3);
    stack_v2.push(2); ASSERT_EQ(stack_v2.top(), 2); ASSERT_EQ(stack_v2.min(), 2);
    stack_v2.push(1); ASSERT_EQ(stack_v2.top(), 1); ASSERT_EQ(stack_v2.min(), 1);
    stack_v2.push(1); ASSERT_EQ(stack_v2.top(), 1); ASSERT_EQ(stack_v2.min(), 1);

//  ================================================================================================

    stack_v2.pop  (); ASSERT_EQ(stack_v2.top(), 1); ASSERT_EQ(stack_v2.min(), 1);
    stack_v2.pop  (); ASSERT_EQ(stack_v2.top(), 2); ASSERT_EQ(stack_v2.min(), 2);
    stack_v2.pop  (); ASSERT_EQ(stack_v2.top(), 5); ASSERT_EQ(stack_v2.min(), 3);
    stack_v2.pop  (); ASSERT_EQ(stack_v2.top(), 3); ASSERT_EQ(stack_v2.min(), 3);
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}