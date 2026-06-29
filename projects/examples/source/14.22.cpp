/////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

/////////////////////////////////////////////////////////////////////////////////

// content : Thread-Safe Stacks

/////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <mutex>
#include <thread>
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

    auto top_and_pop(T & x)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        if (!std::empty(m_container))
        {
            x = m_container.back();

            m_container.pop_back();

            return true;
        }
        else
        {
            return false;
        }
    }

private :

    C m_container;

//  -----------------------------------------------------------------------------

    mutable std::mutex m_mutex;
};

/////////////////////////////////////////////////////////////////////////////////

void produce(Stack < int > & stack)
{
    for (auto i = 1; i < (1 << 10) + 1; ++i)
    {
        stack.push(i);
    }
}

/////////////////////////////////////////////////////////////////////////////////

void consume(Stack < int > & stack)
{
    auto x = 0;

    for (auto i = 0uz; i < 1 << 10; ++i)
    {
        stack.top_and_pop(x);
    }
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    Stack < int > stack_1;

	Stack < int > stack_2 = stack_1;

	Stack < int > stack_3 = std::move(stack_2);

//  --------------------------------------------------

	stack_2 = stack_1;

	stack_3 = std::move(stack_2);

//  --------------------------------------------------

    std::jthread thread_1(produce, std::ref(stack_1));

    std::jthread thread_2(consume, std::ref(stack_1));
}

/////////////////////////////////////////////////////////////////////////////////