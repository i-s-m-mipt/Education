/////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

/////////////////////////////////////////////////////////////////////////////////

// section : Synchronization

/////////////////////////////////////////////////////////////////////////////////

// content : Thread-Safe Stacks

/////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////

template < typename T, typename C = std::vector < T > > class Stack
{
public :

    Stack() = default;

//  -----------------------------------------------------------------------------

    Stack(Stack const & other)
    {
        std::scoped_lock < std::mutex > lock(other.m_mutex);

        m_container = other.m_container;
    }

//  -----------------------------------------------------------------------------

    Stack(Stack && other) : Stack()
    {
        swap(other);
    }

//  -----------------------------------------------------------------------------

    auto & operator=(Stack other)
	{
        swap(other);

		return *this;
	}

//  -----------------------------------------------------------------------------

    void swap(Stack & other)
    {
        std::scoped_lock < std::mutex, std::mutex > lock(m_mutex, other.m_mutex);

        std::swap(m_container, other.m_container);
    }

//  -----------------------------------------------------------------------------

    void push(T x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        m_container.push_back(x);
    }

//  -----------------------------------------------------------------------------

//  auto top() const // error
//  {
//      std::scoped_lock < std::mutex > lock(m_mutex);
//
//      return m_container.back();
//  }

//  -----------------------------------------------------------------------------

//  void pop() // error
//  {
//      std::scoped_lock < std::mutex > lock(m_mutex);
//
//      m_container.pop_back();
//  }

//  -----------------------------------------------------------------------------

    auto top_and_pop()
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        auto x = std::make_shared < T > (m_container.back());

        m_container.pop_back();

        return x;
    }

//  -----------------------------------------------------------------------------

    void top_and_pop(T & x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        x = m_container.back();

        m_container.pop_back();
    }

private :

    C m_container;

//  -----------------------------------------------------------------------------

    mutable std::mutex m_mutex;
};

/////////////////////////////////////////////////////////////////////////////////

// void top_and_pop_v1(Stack < int > & stack) // error
// {
//     std::ignore = stack.top();
// 
//     stack.pop();
// }

/////////////////////////////////////////////////////////////////////////////////

void top_and_pop_v2(Stack < int > & stack)
{
    std::ignore = stack.top_and_pop();
}

/////////////////////////////////////////////////////////////////////////////////

void top_and_pop_v3(Stack < int > & stack)
{
    auto x = 0;

    stack.top_and_pop(x);
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    Stack < int > stack_1;

	Stack < int > stack_2 = stack_1;

	Stack < int > stack_3 = std::move(stack_2);

//  -----------------------------------------------------------------------

	stack_2 = stack_1;

	stack_3 = std::move(stack_2);

//  -----------------------------------------------------------------------
    
    for (auto i = 1; i <= 6; ++i)
    {
        stack_1.push(i);
    }

//  -----------------------------------------------------------------------

    {
//      std::jthread jthread_1(top_and_pop_v1, std::ref(stack_1)); // error

//      std::jthread jthread_2(top_and_pop_v1, std::ref(stack_1)); // error
    }

//  -----------------------------------------------------------------------

    {
        std::jthread jthread_1(top_and_pop_v2, std::ref(stack_1));

        std::jthread jthread_2(top_and_pop_v2, std::ref(stack_1));
    }

//  -----------------------------------------------------------------------

    {
        std::jthread jthread_1(top_and_pop_v3, std::ref(stack_1));

        std::jthread jthread_2(top_and_pop_v3, std::ref(stack_1));
    }
}

/////////////////////////////////////////////////////////////////////////////////