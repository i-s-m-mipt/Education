#include <cassert>
#include <iterator>
#include <stack>

////////////////////////////////////////////////////////////////

template < typename T > class Stack
{
public :

    void push(T x)
    {
        if (std::empty(m_stack)) 
        {
            m_stack.push(x);
            
            m_max = m_stack.top();
        }
        else if (x > m_max) 
        {
            m_stack.push(2 * x - m_max);
            
            m_max = x;
        }
        else 
        {
            m_stack.push(x);
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
 
private :

    std::stack < T > m_stack;
    
    T m_max = T();
};

////////////////////////////////////////////////////////////////

int main()
{

    Stack < int > stack;

//  ------------------------------------------------------------

    stack.push(1); assert(stack.top() == 1 && stack.max() == 1);

    stack.push(3); assert(stack.top() == 3 && stack.max() == 3);

    stack.push(2); assert(stack.top() == 2 && stack.max() == 3);

//  ------------------------------------------------------------

                   assert(stack.top() == 2 && stack.max() == 3);

    stack.pop ( ); assert(stack.top() == 3 && stack.max() == 3);

    stack.pop ( ); assert(stack.top() == 1 && stack.max() == 1);

    stack.pop ( );
}