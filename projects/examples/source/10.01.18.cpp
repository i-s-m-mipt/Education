#include <cassert>
#include <cmath>
#include <iterator>
#include <stack>
#include <utility>

/////////////////////////////////////////////////////////////////////////////

template < typename T > class Stack
{
public:

    void push(T x)
    {
        auto max = std::empty(m_data) ? x : std::max(x, m_data.top().second);

        m_data.emplace(x, max);
    }

    auto top() const
    { 
        return m_data.top().first;
    }
 
    void pop() 
    { 
        m_data.pop();
    }
 
    auto max() const
    { 
        return m_data.top().second;
    }

private:

    std::stack < std::pair < T, T > > m_data;
};

/////////////////////////////////////////////////////////////////////////////

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