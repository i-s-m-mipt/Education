#include <cassert>
#include <cmath>
#include <iterator>
#include <stack>
#include <utility>

///////////////////////////////////////////////////////////////////////////////

template < typename T > class Stack
{
public :

    void push(T x)
    {
        auto max = std::empty(m_stack) ? x : std::max(x, m_stack.top().second);

        m_stack.emplace(x, max);
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

private :

    std::stack < std::pair < T, T > > m_stack;
};

///////////////////////////////////////////////////////////////////////////////

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