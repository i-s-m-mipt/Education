// content : Garbage Collectors

//////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <cstddef>
#include <functional>
#include <memory>
#include <thread>
#include <tuple>

//////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

//////////////////////////////////////////////////////////////////////////

template < typename T > class Stack : private boost::noncopyable
{
private :

    struct Node
    {
        std::shared_ptr < T > x;

        Node * next = nullptr;
    };

public :

   ~Stack()
    {
        while (top_and_pop_v3());
    }

//  ----------------------------------------------------------------------

    void push(T x)
    {
        auto node = new Node(std::make_shared < T > (x), nullptr);

        node->next = m_head.load(std::memory_order::relaxed);

        while
        (
            !m_head.compare_exchange_weak
            (
                node->next, node, 

                std::memory_order::release, 

                std::memory_order::relaxed
            )
        );
    }

//  ----------------------------------------------------------------------

//  void top_and_pop_v1(T & x) // error
//	{
//		auto head = m_head.load();
//
//		while (!m_head.compare_exchange_weak(head, head->next));
//
//		x = head->x;
//	}

//  ----------------------------------------------------------------------

//  auto top_and_pop_v2() // error
//  {
//      auto head = m_head.load();
//
//      while (head && !m_head.compare_exchange_weak(head, head->next));
//
//      return head ? head->x : std::shared_ptr < T > ();
//  }

//  ----------------------------------------------------------------------

    auto top_and_pop_v3()
    {
        m_counter.fetch_add(1, std::memory_order::relaxed);

        auto head = m_head.load(std::memory_order::relaxed);

        while 
        (
            head && !m_head.compare_exchange_weak
            (
                head, head->next,

                std::memory_order::acquire,

                std::memory_order::relaxed
            )
        );

        std::shared_ptr < T > x;

        if (head)
        {
            x.swap(head->x);
        }

        try_clear(head);

        return x;
    }

private :

    void try_clear(Node * head)
    {
        if (m_counter.load(std::memory_order::relaxed) == 1)
        {
            auto tail = m_tail.exchange(nullptr);

            if (!(m_counter.fetch_sub(1, std::memory_order::relaxed) - 1))
            {
                clear(tail);
            }
            else if (tail)
            {
                save_nodes(tail);
            }

            delete head;
        }
        else
        {
            save_node(head);

            m_counter.fetch_sub(1, std::memory_order::relaxed);
        }
    }

//  ----------------------------------------------------------------------

    void clear(Node * nodes) const
    {
        while (nodes)
        {
            auto next = nodes->next;

            delete nodes;

            nodes = next;
        }
    }

//  ----------------------------------------------------------------------

    void save_nodes(Node * nodes)
    {
        auto end = nodes;

        while(auto next = end->next)
        {
            end = next;
        }

        save_nodes(nodes, end);
    }

//  ----------------------------------------------------------------------

    void save_nodes(Node * begin, Node * end)
    {
        end->next = m_tail;

        while (!m_tail.compare_exchange_weak(end->next, begin));
    }

//  ----------------------------------------------------------------------

    void save_node(Node * node)
    {
        save_nodes(node, node);
    }

//  ----------------------------------------------------------------------

    std::atomic < Node * > m_head = nullptr, m_tail = nullptr;

    std::atomic < std::size_t > m_counter = 0;
};

//////////////////////////////////////////////////////////////////////////

void top_and_pop(Stack < int > & stack)
{
    std::ignore = stack.top_and_pop_v3();
}

//////////////////////////////////////////////////////////////////////////

int main()
{
    Stack < int > stack;

//  ---------------------------------------------------------
    
    stack.push(1);

    stack.push(2);

//  ---------------------------------------------------------

    {
        std::jthread jthread_1(top_and_pop, std::ref(stack));

        std::jthread jthread_2(top_and_pop, std::ref(stack));
    }
}

//////////////////////////////////////////////////////////////////////////