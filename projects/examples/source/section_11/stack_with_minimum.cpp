#include <cassert>
#include <stack>

template < typename T > class Stack // note: min element in O(1) time and space
{
public:

    void push(T value)
    {
        if (std::empty(m_stack)) 
        {
            m_stack.push(value); m_minimum = value;
        }
        else if (value < m_minimum) 
        {
            m_stack.push(2 * value - m_minimum); // note: less than value
            
            m_minimum = value;
        }
        else m_stack.push(value);
    }

    [[nodiscard]] T top() const noexcept(noexcept(m_stack.top()))
    {
        return (m_stack.top() < m_minimum ? m_minimum : m_stack.top());
    }

    void pop() noexcept(noexcept(m_stack.top()) && noexcept(m_stack.pop()))
    {
        if (m_stack.top() < m_minimum) // note: update current minimum
        {
            (m_minimum *= 2)-= m_stack.top();
        }

        m_stack.pop();
    }

    [[nodiscard]] auto size() const noexcept(noexcept(m_stack.size()))
	{ 
		return m_stack.size(); 
	}
 
    [[nodiscard]] auto min() const noexcept { return m_minimum; }
 
private:

    std::stack < T > m_stack; T m_minimum;

}; // template < typename T > class Stack 

int main()
{
    Stack < int > stack;
   
    stack.push(3); assert(stack.top() == 3 && stack.min() == 3);
    stack.push(5); assert(stack.top() == 5 && stack.min() == 3);
    stack.push(2); assert(stack.top() == 2 && stack.min() == 2);
    stack.push(1); assert(stack.top() == 1 && stack.min() == 1);
    stack.push(1); assert(stack.top() == 1 && stack.min() == 1);

    stack.pop  (); assert(stack.top() == 1 && stack.min() == 1);
    stack.pop  (); assert(stack.top() == 2 && stack.min() == 2);
    stack.pop  (); assert(stack.top() == 5 && stack.min() == 3);
    stack.pop  (); assert(stack.top() == 3 && stack.min() == 3);
 
    return 0;
}