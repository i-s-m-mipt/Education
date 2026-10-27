////////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

////////////////////////////////////////////////////////////////////////////////////////////////////

// content : Lockfree Queues
//
// content : Single-Producer Single-Consumer (SPSC) Queues

////////////////////////////////////////////////////////////////////////////////////////////////////

// support : https://lmax-exchange.github.io/disruptor/files/Disruptor-1.0.pdf

////////////////////////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <functional>
#include <iterator>
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

    auto size() const
    {
        return m_size;
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

struct alignas(std::hardware_destructive_interference_size) Agent
{
    std::atomic < std::size_t > size = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

void produce(Storage < int > & storage, Agent & producer, Agent const & consumer, std::size_t size)
{
    std::this_thread::sleep_for(1s);

    auto p = 0uz, c = 0uz, cached_c = consumer.size.load(std::memory_order::acquire);

    auto storage_size = std::size(storage);

    auto x = 0;

    for (auto i = 0uz; i < size; ++i)
    {
        p = producer.size.load(std::memory_order::relaxed);

        if (p - cached_c >= storage_size)
        {
            while (p - (c = consumer.size.load(std::memory_order::acquire)) >= storage_size)
            {
                _mm_pause();
            }

            cached_c = c;
        }

        storage[p] = ++x;

        producer.size.store(p + 1, std::memory_order::release);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void consume(Storage < int > & storage, Agent const & producer, Agent & consumer, std::size_t size)
{
    auto p = 0uz, c = consumer.size.load(std::memory_order::relaxed);

    auto x = 0;

    while (size != 0)
    {
        std::print("consume\n");

        while ((p = producer.size.load(std::memory_order::acquire)) == c)
        {
            _mm_pause();
        }

        while (c != p && size != 0)
        {
            x = storage[c++];

            std::print("consume : x = {}\n", x);

            --size;
        }

        consumer.size.store(c, std::memory_order::release);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(std::atomic < std::size_t > ::is_always_lock_free);

//  ------------------------------------------------------------------------------------------------

    auto size = 1uz << 10;

//  ------------------------------------------------------------------------------------------------

    Storage < int > storage(size);

//  ------------------------------------------------------------------------------------------------

    Agent producer;

    Agent consumer;

//  ------------------------------------------------------------------------------------------------

    std::jthread thread_1(produce, std::ref(storage), std::ref(producer), std::ref(consumer), size);

    std::jthread thread_2(consume, std::ref(storage), std::ref(producer), std::ref(consumer), size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////