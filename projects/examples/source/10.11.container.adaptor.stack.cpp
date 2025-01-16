#include <cassert>
#include <cmath>
#include <iterator>
#include <stack>
#include <utility>

//  ================================================================================================

template < typename T > class Stack_v1
{
public:

    void push(T value)
    {
        auto max = std::empty(m_data) ? value : std::max(value, m_data.top().second);

        m_data.emplace(value, max);
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

//  ================================================================================================

template < typename T > class Stack_v2
{
public:

    void push(T value)
    {
        if (std::empty(m_data)) 
        {
            m_data.push(value); m_max = m_data.top();
        }
        else if (value > m_max) 
        {
            m_data.push(2 * value - m_max); m_max = value;
        }
        else 
        {
            m_data.push(value);
        }
    }

    auto top() const
    {
        return m_data.top() > m_max ? m_max : m_data.top();
    }

    void pop()
    {
        if (auto t = m_data.top(); t > m_max) 
        {
            (m_max *= 2) -= t;
        }

        m_data.pop();
    }
 
    auto max() const
    { 
        return m_max; 
    }
 
private:

    std::stack < T > m_data; T m_max = T();
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