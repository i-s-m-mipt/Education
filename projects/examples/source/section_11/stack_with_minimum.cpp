#include <cassert>
#include <cmath>
#include <stack>
#include <type_traits>
#include <utility>

template < typename T > class Stack_v1 // note: min element in O(1) time and O(N) space complexity
{
public:

    void push(T value)
    {
        m_stack.emplace(value, (std::empty(m_stack) ? value : std::min(value, m_stack.top().second)));
    }

    [[nodiscard]] T top() const noexcept { return m_stack.top().first; }
 
    void pop() noexcept { m_stack.pop(); }
 
    [[nodiscard]] std::size_t size() const noexcept { return m_stack.size(); }
 
    [[nodiscard]] T min() const noexcept { return m_stack.top().second; }

private:

    std::stack < std::pair < T, T > > m_stack; // note: consider additional stack for extremums

}; // template < typename T > class Stack_v1

template < typename T > requires std::is_arithmetic_v < T > class Stack_v2
{
public:

    void push(T value)
    {
        if (std::empty(m_stack)) 
        {
            m_stack.push(value); m_min = m_stack.top();
        }
        else if (value < m_min) 
        {
            m_stack.push(2 * value - m_min); m_min = value; // note: less than value
        }
        else 
        {
            m_stack.push(value);
        }
    }

    [[nodiscard]] T top() const noexcept
    {
        return (m_stack.top() < m_min ? m_min : m_stack.top());
    }

    void pop() noexcept
    {
        if (auto t = m_stack.top(); t < m_min) 
        {
            (m_min *= 2) -= t; // note: update current minimum
        }

        m_stack.pop();
    }

    [[nodiscard]] std::size_t size() const noexcept { return m_stack.size(); }
 
    [[nodiscard]] T min() const noexcept { return m_min; }
 
private:

    std::stack < T > m_stack; 
    
    T m_min; // note: min element in O(1) time and space complexity

}; // template < typename T > requires std::is_arithmetic_v < T > class Stack_v2 

int main()
{
    Stack_v1 < int > stack_v1;

    stack_v1.push(3); assert(stack_v1.top() == 3 && stack_v1.min() == 3);
    stack_v1.push(5); assert(stack_v1.top() == 5 && stack_v1.min() == 3);
    stack_v1.push(2); assert(stack_v1.top() == 2 && stack_v1.min() == 2);
    stack_v1.push(1); assert(stack_v1.top() == 1 && stack_v1.min() == 1);
    stack_v1.push(1); assert(stack_v1.top() == 1 && stack_v1.min() == 1);

    stack_v1.pop  (); assert(stack_v1.top() == 1 && stack_v1.min() == 1);
    stack_v1.pop  (); assert(stack_v1.top() == 2 && stack_v1.min() == 2);
    stack_v1.pop  (); assert(stack_v1.top() == 5 && stack_v1.min() == 3);
    stack_v1.pop  (); assert(stack_v1.top() == 3 && stack_v1.min() == 3);

    Stack_v2 < int > stack_v2;
   
    stack_v2.push(3); assert(stack_v2.top() == 3 && stack_v2.min() == 3);
    stack_v2.push(5); assert(stack_v2.top() == 5 && stack_v2.min() == 3);
    stack_v2.push(2); assert(stack_v2.top() == 2 && stack_v2.min() == 2);
    stack_v2.push(1); assert(stack_v2.top() == 1 && stack_v2.min() == 1);
    stack_v2.push(1); assert(stack_v2.top() == 1 && stack_v2.min() == 1);

    stack_v2.pop  (); assert(stack_v2.top() == 1 && stack_v2.min() == 1);
    stack_v2.pop  (); assert(stack_v2.top() == 2 && stack_v2.min() == 2);
    stack_v2.pop  (); assert(stack_v2.top() == 5 && stack_v2.min() == 3);
    stack_v2.pop  (); assert(stack_v2.top() == 3 && stack_v2.min() == 3);
 
    return 0;
}