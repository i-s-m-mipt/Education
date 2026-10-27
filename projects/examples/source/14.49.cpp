////////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

////////////////////////////////////////////////////////////////////////////////////////////////////

// content : Lockfree Queues

////////////////////////////////////////////////////////////////////////////////////////////////////

// support : https://lmax-exchange.github.io/disruptor/files/Disruptor-1.0.pdf

////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////////////////////

#include <xmmintrin.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Storage
{
public :

    Storage(std::size_t size) : m_size(size), m_mask(size - 1)
    {
        assert(m_size != 0 && (m_size & m_mask) == 0);

        m_array = static_cast < T * >
        (
            operator new(sizeof(T) * m_size, std::align_val_t(s_alignment))
        );

        for (auto i = 0uz; i < m_size; ++i)
        {
            std::construct_at(&m_array[i]);
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

////////////////////////////////////////////////////////////////////////////////////////////////////

using index_t = std::int64_t;

////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////

void produce(Storage < int > & storage, Index & producer, Index const & consumer, index_t size)
{
    std::this_thread::sleep_for(1s);

    index_t p = 0, c = 0, cached_consumer = -1;

    for (auto i = 1; i < (1 << 10) + 1; ++i)
    {
        p = producer.get(std::memory_order::relaxed) + 1;

        if (p - size > cached_consumer)
        {
            while ((c = consumer.get(std::memory_order::acquire)) < p - size)
            {
                _mm_pause();
            }

            cached_consumer = c;
        }

        storage[p] = i;

        producer.set(p, std::memory_order::release);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void consume(Storage < int > const & storage, Index const & producer, Index & consumer)
{
    index_t c = 0, p = 0;

    while (c < 1 << 10)
    {
        std::print("consume\n");

        while ((p = producer.get(std::memory_order::acquire)) < c)
        {
            _mm_pause();
        }

        while (c <= p)
        {
            auto x = storage[c++];

            std::print("consume : x = {}\n", x);
        }

        consumer.set(c - 1, std::memory_order::release);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(std::atomic < index_t > ::is_always_lock_free);

//  ------------------------------------------------------------------------------------------------

    auto size = 1 << 10;

//  ------------------------------------------------------------------------------------------------

    Storage < int > storage(size);

//  ------------------------------------------------------------------------------------------------

    Index producer;

    Index consumer;

//  ------------------------------------------------------------------------------------------------

    std::jthread thread_1(produce, std::ref(storage), std::ref(producer), std::ref(consumer), size);

    std::jthread thread_2(consume, std::ref(storage), std::ref(producer), std::ref(consumer)      );
}

////////////////////////////////////////////////////////////////////////////////////////////////////