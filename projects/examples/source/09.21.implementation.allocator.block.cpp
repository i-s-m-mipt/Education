#include <bit>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

//  ================================================================================================

class Block_Allocator : private boost::noncopyable
{
private:

    struct Node { std::size_t size = 0; Node * next = nullptr; };

	struct alignas(std::max_align_t) Header { std::size_t size = 0; };

public:
	
    explicit Block_Allocator(std::size_t size) : m_size(size)
    {
        if (m_size >= sizeof(Node) + 1) 
        {
            m_begin = ::operator new(m_size, default_alignment);

	        m_head = get_node(m_begin); *m_head = { m_size - sizeof(Header), nullptr };
        }
        else throw std::runtime_error("invalid size");
    }
	
   ~Block_Allocator() noexcept
    {
        ::operator delete(m_begin, m_size, default_alignment);
    }

public:

    [[nodiscard]] void * allocate(std::size_t size) noexcept
    {
	    void * const end = get_byte(m_begin) + sizeof(Header) + size, * next = end;

	    auto space = 2 * alignof(Header);

        if (next = std::align(alignof(Header), sizeof(Header), next, space); next)
        {
            auto padding = get_byte(next) - get_byte(end);

            if (const auto [current, previous] = find_first(size + padding); current)
            {
                if (current->size >= size + padding + sizeof(Node) + 1)
                {
                    const auto block_size = sizeof(Header) + size + padding;

                    const auto new_node = get_node(get_byte(current) + block_size);

                    new_node->size = current->size - block_size;
                       
                    new_node->next = current->next; current->next = new_node;
                }
                else
                {
                    padding += current->size - (size + padding);
                }

                if (!previous)
                {
                    m_head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                const auto header = get_header(current); header->size = size + padding;

                return get_byte(current) + sizeof(Header);
            }
            else return nullptr;
        }
        else return nullptr;
    }

    void deallocate(void * ptr) noexcept
    {
        const auto header = get_header(get_byte(ptr) - sizeof(Header));

        const auto node = get_node(header); node->size = header->size;

        Node * previous = nullptr;
        
        for (auto current = m_head; current; previous = current, current = current->next)
        {
            if (node < current)
            {
                if (node->next = current; !previous)
                {
                    m_head = node;
                }
                else
                {
                    previous->next = node;
                }

                break;
            }
        }

        merge(previous, node);
    }

    void print() const 
    { 
        std::cout << std::bit_cast < std::size_t > (m_head);

        if (m_head->next)
        {
            std::cout << ' ' << std::bit_cast < std::size_t > (m_head->next);
        }

        std::cout << std::endl;
    }

private:

    [[nodiscard]] std::byte * get_byte(void * ptr) const noexcept
	{
		return static_cast < std::byte * > (ptr);
	}

    [[nodiscard]] Node * get_node(void * ptr) const noexcept
	{
		return static_cast < Node * > (ptr);
	}

    [[nodiscard]] Header * get_header(void * ptr) const noexcept
	{
		return static_cast < Header * > (ptr);
	}

    [[nodiscard]] std::pair < Node * , Node * > find_first(std::size_t size) const
    {
        Node * current = m_head, * previous = nullptr;

	    for (; current && size > current->size; previous = current, current = current->next) {}

        return std::make_pair(current, previous);
    }

	void merge(Node * previous, Node * node) const noexcept
    {
	    if (node->next && get_byte(node) + node->size + sizeof(Header) == get_byte(node->next))
	    {
		    node->size += node->next->size + sizeof(Header);
		    node->next  = node->next->next;
	    }

	    if (previous && get_byte(previous) + previous->size + sizeof(Header) == get_byte(node))
	    {
		    previous->size += node->size + sizeof(Header);
		    previous->next  = node->next;
	    }
    }

public:

	static constexpr std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

    const std::size_t m_size;

private:

    void * m_begin = nullptr;
    Node * m_head  = nullptr;

}; // class Block_Allocator : private boost::noncopyable

//  ================================================================================================

void test_1(benchmark::State & state)
{
	constexpr std::size_t kb = 1024, mb = kb * kb, gb = kb * kb * kb;

    std::mt19937_64 engine(state.range(0));

    std::uniform_int_distribution distribution(1, 16);

    std::vector < void * > pointers(kb, nullptr);

	for (auto _ : state)
	{
		Block_Allocator allocator(16 * gb);

		for (std::size_t i = 0; i < kb; i +=  1) pointers[i] = allocator.  allocate(distribution(engine) * mb);
		for (std::size_t i = 0; i < kb; i += 32)               allocator.deallocate(pointers[i]              );
		for (std::size_t i = 0; i < kb; i += 32) pointers[i] = allocator.  allocate(distribution(engine) * mb);
		for (std::size_t i = 0; i < kb; i +=  1)               allocator.deallocate(pointers[i]              );
	}
}

//  ================================================================================================

void test_2(benchmark::State & state)
{
	constexpr std::size_t kb = 1024, mb = kb * kb;

    std::mt19937_64 engine(state.range(0));

    std::uniform_int_distribution distribution(1, 16);

    std::vector < std::pair < void * , std::size_t > > blocks(kb);

	for (auto _ : state)
	{
		for (std::size_t i = 0; i < kb; i +=  1) 
        {
            auto size = distribution(engine) * mb; blocks[i] = { ::operator new(size), size };
        }
        
		for (std::size_t i = 0; i < kb; i += 32) ::operator delete(blocks[i].first, blocks[i].second);

		for (std::size_t i = 0; i < kb; i += 32)
        {
            auto size = distribution(engine) * mb; blocks[i] = { ::operator new(size), size };
        } 
        
		for (std::size_t i = 0; i < kb; i +=  1) ::operator delete(blocks[i].first, blocks[i].second);
	}
}

//  ================================================================================================

BENCHMARK(test_1)->Arg(42);
BENCHMARK(test_2)->Arg(42);

//  ================================================================================================

int main(int argc, char ** argv)
{
    Block_Allocator allocator(1024);                           allocator.print(); // detail: X

	[[maybe_unused]] auto ptr_A = allocator.  allocate(   16); allocator.print(); // detail: X + 32
	[[maybe_unused]] auto ptr_B = allocator.  allocate(   32); allocator.print(); // detail: X + 32 + 48
	[[maybe_unused]] auto ptr_C = allocator.  allocate(   32); allocator.print(); // detail: X + 32 + 48 + 48
    [[maybe_unused]] auto ptr_D = allocator.  allocate(   16); allocator.print(); // detail: X + 32 + 48 + 48 + 32

	                              allocator.deallocate(ptr_B); allocator.print(); // detail: X + 32
                                  allocator.deallocate(ptr_C); allocator.print(); // detail: X + 32

	[[maybe_unused]] auto ptr_E = allocator.  allocate(   16); allocator.print(); // detail: X + 32 + 32
	[[maybe_unused]] auto ptr_F = allocator.  allocate(   32); allocator.print(); // detail: X + 32 + 48 + 48 + 32
    
    // detail: HAHBBHCCHDD -> HA000000HDD -> HAHEHFF0HDD

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}