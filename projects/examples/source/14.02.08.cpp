///////////////////////////////////////////////////////////////////////////

#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////

template < typename T, typename C = std::vector < T > >  class Stack
{
public :

    using mutex_t = std::mutex;

//  -----------------------------------------------------------------------

    Stack() = default;

//  -----------------------------------------------------------------------

    Stack(Stack const & other)
    {
        std::scoped_lock < mutex_t > lock(other.m_mutex);

        m_container = other.m_container;
    }

//  -----------------------------------------------------------------------

    Stack(Stack && other)
    {
        std::scoped_lock < mutex_t > lock(other.m_mutex);

        m_container = std::move(other.m_container);
    }

//  -----------------------------------------------------------------------

    auto & operator=(Stack const & other)
    {
        std::scoped_lock < mutex_t, mutex_t > lock(m_mutex, other.m_mutex);

        m_container = other.m_container;

        return *this;
    }

//  -----------------------------------------------------------------------

    auto & operator=(Stack && other)
    {
        std::scoped_lock < mutex_t, mutex_t > lock(m_mutex, other.m_mutex);

        m_container = std::move(other.m_container);

        return *this;
    }

//  -----------------------------------------------------------------------

    void push(T x)
    {
        std::scoped_lock < mutex_t > lock(m_mutex);

        m_container.push_back(x);
    }

//  -----------------------------------------------------------------------

//  auto top() const // error
//  {
//      std::scoped_lock < mutex_t > lock(m_mutex);
//
//      return m_container.back();
//  }

//  -----------------------------------------------------------------------

//  void pop() // error
//  {
//      std::scoped_lock < mutex_t > lock(m_mutex);
//
//      m_container.pop_back();
//  }

//  -----------------------------------------------------------------------

    auto top_and_pop()
    {
        std::scoped_lock < mutex_t > lock(m_mutex);

        auto x = std::make_shared < T > (m_container.back());

        m_container.pop_back();

        return x;
    }

//  -----------------------------------------------------------------------

    void top_and_pop(T & x)
    {
        std::scoped_lock < mutex_t > lock(m_mutex);

        x = m_container.back();

        m_container.pop_back();
    }

private :

    C m_container;

//  -----------------------------------------------------------------------

    mutable mutex_t m_mutex;
};

///////////////////////////////////////////////////////////////////////////

// void top_and_pop_v1(Stack < int > & stack) // error
// {
//     std::ignore = stack.top();
// 
//     stack.pop();
// }

///////////////////////////////////////////////////////////////////////////

void top_and_pop_v2(Stack < int > & stack)
{
    std::ignore = stack.top_and_pop();
}

///////////////////////////////////////////////////////////////////////////

int main()
{
    Stack < int > stack;

//  --------------------------------------------------------------------
    
    stack.push(1);

    stack.push(2);

//  --------------------------------------------------------------------

    {
//      std::jthread thread_1(top_and_pop_v1, std::ref(stack)); // error

//      std::jthread thread_2(top_and_pop_v1, std::ref(stack)); // error
    }

//  --------------------------------------------------------------------

    {
        std::jthread thread_1(top_and_pop_v2, std::ref(stack));

        std::jthread thread_2(top_and_pop_v2, std::ref(stack));
    }
}

///////////////////////////////////////////////////////////////////////////