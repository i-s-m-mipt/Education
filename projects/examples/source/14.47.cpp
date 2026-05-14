/////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

/////////////////////////////////////////////////////////////////////////////////

// section : Atomics

/////////////////////////////////////////////////////////////////////////////////

// content : Lock-Free Programming
//
// content : Thread-Safe Lock-Free Stacks
//
// content : Hazard Pointers
//
// content : Garbage Collectors

/////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <cstddef>
#include <functional>
#include <thread>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////

template < typename T > class Pointer
{
public :

    std::atomic < std::thread::id > id = std::thread::id();

    std::atomic < T * > x = nullptr;
};

/////////////////////////////////////////////////////////////////////////////////

template < typename T > class Handler
{
public :

    Handler()
    {
        for (auto & pointer : s_pointers)
        {
            std::thread::id id;

            if
            (
                pointer.id.compare_exchange_strong
                (
                    id,

                    std::this_thread::get_id(),

                    std::memory_order::acquire,

                    std::memory_order::relaxed
                )
            )
            {
                m_pointer = &pointer;

                break;
            }
        }
    }

//  -----------------------------------------------------------------------------

   ~Handler()
    {
        m_pointer->x.store(nullptr, std::memory_order::relaxed);

        m_pointer->id.store(std::thread::id(), std::memory_order::release);
    }

//  -----------------------------------------------------------------------------

    auto & get() const
    {
        return m_pointer->x;
    }

//  -----------------------------------------------------------------------------

    static auto has_pointers(T * x)
    {
        for (auto & pointer : s_pointers)
        {
            if (pointer.id.load(std::memory_order::acquire) != std::thread::id())
            {
                if (pointer.x.load(std::memory_order::relaxed) == x)
                {
                    return true;
                }
            }
        }

        return false;
    }

private :

    Pointer < T > * m_pointer = nullptr;

//  -----------------------------------------------------------------------------

    static inline auto s_pointers = std::vector < Pointer < T > > (64);
};

/////////////////////////////////////////////////////////////////////////////////

template < typename T > class Storage
{
private :

    class Node
    {
    public :

       ~Node()
        {
            delete x;
        }

    //  ----------------------

        T * x = nullptr;

        Node * next = nullptr;
    };

public :

    void push_back(T * x)
    {
        push_back(new Node(x, nullptr));

        m_size.fetch_add(1, std::memory_order::relaxed);
    }

//  ---------------------------------------------------------------------

    void try_clear()
    {
        if (m_size.load(std::memory_order::relaxed) >= 64)
        {
            clear();
        }
    }

private :

    void push_back(Node * node)
    {
        node->next = m_head.load(std::memory_order::relaxed);

        while
        (
            !m_head.compare_exchange_weak
            (
                node->next,

                node,

                std::memory_order::release,

                std::memory_order::relaxed
            )
        );
    }

//  ---------------------------------------------------------------------

    void clear()
    {
        auto node = m_head.exchange(nullptr, std::memory_order::acquire);

        m_size.store(0, std::memory_order::relaxed);

        auto size = 0uz;

        while (node)
        {
            auto next = node->next;

            if (!Handler < T > ::has_pointers(node->x))
            {
                delete node;
            }
            else
            {
                push_back(node);

                ++size;
            }

            node = next;
        }

        if (size > 0)
        {
            m_size.fetch_add(size, std::memory_order::relaxed);
        }
    }

//  ---------------------------------------------------------------------

    std::atomic < Node * > m_head = nullptr;

    std::atomic < std::size_t > m_size = 0;
};

/////////////////////////////////////////////////////////////////////////////////

template < typename T > class Stack
{
private :

    struct Node
    {
        T x = T();

        Node * next = nullptr;
    };

public :

   ~Stack()
    {
        T x = T();

        while (top_and_pop(x));
    }

//  -------------------------------------------------------------------

    void push(T x)
    {
        auto node = new Node(x, nullptr);

        node->next = m_head.load(std::memory_order::relaxed);

        while
        (
            !m_head.compare_exchange_weak
            (
                node->next,

                node,

                std::memory_order::release,

                std::memory_order::relaxed
            )
        );
    }

//  -------------------------------------------------------------------

    auto top_and_pop(T & x)
    {
        auto & pointer = get_pointer();

        auto head = m_head.load(std::memory_order::acquire);

        do
        {
            Node * node = nullptr;

            do
            {
                node = head;

                pointer.store(head);

                head = m_head.load(std::memory_order::acquire);
            }
            while (head != node);
        }
        while
        (
            head && !m_head.compare_exchange_strong
            (
                head,

                head->next,

                std::memory_order::acquire,

                std::memory_order::relaxed
            )
        );

        pointer.store(nullptr, std::memory_order::release);

        if (head)
        {
            x = head->x;

            if (Handler < Node > ::has_pointers(head))
            {
                m_storage.push_back(head);
            }
            else
            {
                delete head;
            }

            m_storage.try_clear();

            return true;
        }

        return false;
    }

private :

    auto & get_pointer()
    {
        thread_local static Handler < Node > handler;

        return handler.get();
    }

//  -------------------------------------------------------------------

    std::atomic < Node * > m_head = nullptr;

    Storage < Node > m_storage;
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
    Stack < int > stack;

//  ------------------------------------------------

    std::jthread thread_1(produce, std::ref(stack));

    std::jthread thread_2(consume, std::ref(stack));
}

/////////////////////////////////////////////////////////////////////////////////