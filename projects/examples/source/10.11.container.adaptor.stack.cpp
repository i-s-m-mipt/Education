#include <cassert>
#include <cmath>
#include <iterator>
#include <stack>
#include <utility>

//  ================================================================================================

template < typename T > class Stack_v1
{
public:

    void push(T data)
    {
        auto max = std::empty(m_stack) ? data : std::max(data, m_stack.top().second);

        m_stack.emplace(data, max);
    }

    auto top() const
    { 
        return m_stack.top().first; 
    }
 
    void pop() 
    { 
        m_stack.pop(); 
    }
 
    auto max() const
    { 
        return m_stack.top().second; 
    }

private:

    std::stack < std::pair < T, T > > m_stack;
};

//  ================================================================================================

template < typename T > class Stack_v2
{
public:

    void push(T data)
    {
        if (std::empty(m_stack)) 
        {
            m_stack.push(data); m_max = m_stack.top();
        }
        else if (data > m_max) 
        {
            m_stack.push(2 * data - m_max); m_max = data;
        }
        else 
        {
            m_stack.push(data);
        }
    }

    auto top() const
    {
        return m_stack.top() > m_max ? m_max : m_stack.top();
    }

    void pop()
    {
        if (auto t = m_stack.top(); t > m_max) 
        {
            (m_max *= 2) -= t;
        }

        m_stack.pop();
    }
 
    auto max() const
    { 
        return m_max; 
    }
 
private:

    std::stack < T > m_stack; T m_max = T();
};

//  ================================================================================================

int main()
{
    Stack_v1 < int > stack_v1;

//  ---------------------------------------------------------------------------

    stack_v1.push(1); assert(stack_v1.top() == 1); assert(stack_v1.max() == 1);
    stack_v1.push(3); assert(stack_v1.top() == 3); assert(stack_v1.max() == 3);
    stack_v1.push(2); assert(stack_v1.top() == 2); assert(stack_v1.max() == 3);

//  ---------------------------------------------------------------------------

                      assert(stack_v1.top() == 2); assert(stack_v1.max() == 3);
    stack_v1.pop ( ); assert(stack_v1.top() == 3); assert(stack_v1.max() == 3);
    stack_v1.pop ( ); assert(stack_v1.top() == 1); assert(stack_v1.max() == 1);
    stack_v1.pop ( );

//  ---------------------------------------------------------------------------

    Stack_v2 < int > stack_v2;
   
//  ---------------------------------------------------------------------------

    stack_v2.push(1); assert(stack_v2.top() == 1); assert(stack_v2.max() == 1);
    stack_v2.push(3); assert(stack_v2.top() == 3); assert(stack_v2.max() == 3);
    stack_v2.push(2); assert(stack_v2.top() == 2); assert(stack_v2.max() == 3);

//  ---------------------------------------------------------------------------

                      assert(stack_v2.top() == 2); assert(stack_v2.max() == 3);
    stack_v2.pop ( ); assert(stack_v2.top() == 3); assert(stack_v2.max() == 3);
    stack_v2.pop ( ); assert(stack_v2.top() == 1); assert(stack_v2.max() == 1);
    stack_v2.pop ( );
}