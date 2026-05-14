///////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

///////////////////////////////////////////////////////////////////////////////////////////////////

// section : Atomics

///////////////////////////////////////////////////////////////////////////////////////////////////

// content : Thread-Safe Lock-Free Queues
//
// content : Pattern Disruptor

///////////////////////////////////////////////////////////////////////////////////////////////////

// support : https://lmax-exchange.github.io/disruptor/files/Disruptor-1.0.pdf

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <new>
#include <print>
#include <thread>
#include <tuple>

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Storage
{
public :

    Storage(std::size_t size) : m_size(size), m_mask(size - 1)
    {
        assert((m_size & m_mask) == 0);

        m_array = static_cast < T * >
        (
            operator new(sizeof(T) * m_size, std::align_val_t(s_alignment))
        );

        for (auto i = 0uz; i < m_size; ++i)
        {
            std::construct_at(&m_array[i], T());
        }
    }

//  ------------------------------------------------------------------------------------

   ~Storage()
    {
        std::destroy(m_array, m_array + m_size);

        operator delete(m_array, sizeof(T) * m_size, std::align_val_t(s_alignment));
    }

//  ------------------------------------------------------------------------------------

    auto       & operator[](std::size_t index)       { return m_array[index & m_mask]; }

    auto const & operator[](std::size_t index) const { return m_array[index & m_mask]; }

private :

    T * m_array = nullptr;

    std::size_t m_size = 0, m_mask = 0;

//  ------------------------------------------------------------------------------------

    static inline auto s_alignment = std::hardware_destructive_interference_size;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

using index_t = std::int64_t;

///////////////////////////////////////////////////////////////////////////////////////////////////

class alignas(std::hardware_destructive_interference_size) Index
{
public :

    auto get(std::memory_order order) const
    {
        return m_index.load(order);
    }

//  ----------------------------------------------------------------------------------

    void set(index_t index, std::memory_order order)
    {
        m_index.store(index, order);
    }

private :

    std::atomic < index_t > m_index = -1;

    std::byte m_padding
    [
        std::hardware_destructive_interference_size - sizeof(std::atomic < index_t > )
    ];
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class Controller
{
public :

    Controller(index_t size, Index & producer_index, Index const & consumer_index)
    :
        m_size(size),

        m_producer_index(producer_index),

        m_consumer_index(consumer_index)
    {}

//  ------------------------------------------------------------------------------

    auto get() const
    {
        auto i = m_producer_index.get(std::memory_order::relaxed) + 1;

        if (auto j = i - m_size; j > m_cached_consumer_index)
        {
            index_t k = 0;

            while ((k = m_consumer_index.get(std::memory_order::acquire)) < j)
            {
                __builtin_ia32_pause();
            }

            m_cached_consumer_index = k;
        }

        return i;
    }

//  ------------------------------------------------------------------------------

    void set(index_t index) const
    {
        m_producer_index.set(index, std::memory_order::release);
    }

private :

    index_t m_size = 0;

//  ------------------------------------------------------------------------------

    Index       & m_producer_index;

    Index const & m_consumer_index;

//  ------------------------------------------------------------------------------

    mutable index_t m_cached_consumer_index = -1;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

void produce(Storage < int > & storage, Controller const & controller)
{
    std::this_thread::sleep_for(1s);

    for (auto i = 1; i < (1 << 10) + 1; ++i)
    {
        auto j = controller.get();

        storage[j] = i;

        controller.set(j);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void consume(Storage < int > const & storage, Index const & producer_index, Index & consumer_index)
{
    index_t i = 0;

    while (i < 1 << 10)
    {
        std::print("consume\n");

        index_t j = 0;

        while ((j = producer_index.get(std::memory_order::acquire)) < i)
        {
            __builtin_ia32_pause();
        }

        while (i <= j)
        {
            auto x = storage[i++];

            std::print("consume : x = {}\n", x);
        }

        consumer_index.set(i - 1, std::memory_order::release);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto size = 1 << 10;

//  ----------------------------------------------------------------------------------

    Storage < int > storage(size);

//  ----------------------------------------------------------------------------------

    Index producer_index;

    Index consumer_index;

//  ----------------------------------------------------------------------------------

    Controller controller(size, producer_index, consumer_index);

//  ----------------------------------------------------------------------------------

    std::jthread thread_1(produce, std::ref(storage), std::ref(controller));

    std::jthread thread_2
    (
        consume, std::ref(storage), std::ref(producer_index), std::ref(consumer_index)
    );
}

///////////////////////////////////////////////////////////////////////////////////////////////////