////////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <tuple>

////////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Stack : private boost::noncopyable
{
private :

    struct Node
    {
        std::shared_ptr < T > x;

        std::atomic < std::shared_ptr < Node > > next;
    };

public :

   ~Stack()
    {
        while (top_and_pop());
    }

//  --------------------------------------------------------------------------------

    void push(T x)
    {
        auto node = std::make_shared < Node > (std::make_shared < T > (x), nullptr);

        auto expected = m_head.load(std::memory_order::relaxed);

        do
        {
            node->next = expected;
        }
        while 
        (
            !m_head.compare_exchange_weak
            (
                expected, node, 

                std::memory_order::release, 

                std::memory_order::relaxed
            )
        );
    }

//  --------------------------------------------------------------------------------

    auto top_and_pop()
    {
        auto head = m_head.load(std::memory_order::relaxed);

        while 
        (
            head && !m_head.compare_exchange_weak
            (
                head, head->next.load(std::memory_order::relaxed),

                std::memory_order::acquire,

                std::memory_order::relaxed
            )
        );

        if (head)
        {
            head->next = std::shared_ptr < Node > ();

            return head->x;
        }

        return std::shared_ptr < T > ();
    }

private :

    std::atomic < std::shared_ptr < Node > > m_head = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////

void top_and_pop(Stack < int > & stack)
{
    std::ignore = stack.top_and_pop();
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(!std::atomic < std::shared_ptr < int > >::is_always_lock_free);

//  -----------------------------------------------------------------------------

    Stack < int > stack;

//  -----------------------------------------------------------------------------
    
    stack.push(1);

    stack.push(2);

//  -----------------------------------------------------------------------------

    {
        std::jthread jthread_1(top_and_pop, std::ref(stack));

        std::jthread jthread_2(top_and_pop, std::ref(stack));
    }
}

////////////////////////////////////////////////////////////////////////////////////