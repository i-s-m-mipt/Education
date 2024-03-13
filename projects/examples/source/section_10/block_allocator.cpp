#include <bit>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

class Block_Allocator : private boost::noncopyable // note: deallocations at any position for blocks of different sizes
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

    [[nodiscard]] void * allocate(std::size_t size) noexcept
    {
	    void * end = get_byte(m_begin) + sizeof(Header) + size, * next = end;

	    auto space = 2 * alignof(Header); // note: enough space to align next pointer to Header

        if (next = std::align(alignof(Header), sizeof(Header), next, space); next) // note: modifies next and space
        {
            auto padding = get_byte(next) - get_byte(end); // note: padding between end of data and aligned header

            if (auto [current, previous] = find_first(size + padding); current) // note: consider also find best
            {
                if (current->size >= size + padding + sizeof(Node) + 1) // note: new splitted node for the rest
                {
                    auto block_size = sizeof(Header) + size + padding;

                    auto new_node = get_node(get_byte(current) + block_size);

                    new_node->size = current->size - block_size;
                       
                    new_node->next = current->next; current->next = new_node;
                }
                else
                {
                    padding += current->size - (size + padding); // note: not enough space for splitting nodes
                }

                if (!previous)
                {
                    m_head = current->next; // note: allocated on head node
                }
                else
                {
                    previous->next = current->next; // note: head skipped
                }

                auto header = get_header(current); header->size = size + padding;

                return get_byte(current) + sizeof(Header);
            }
            else return nullptr;
        }
        else return nullptr;
    }

    void deallocate(void * ptr) noexcept
    {
        auto header = get_header(get_byte(ptr) - sizeof(Header));

        auto node = get_node(header); node->size = header->size;

        Node * previous = nullptr;
        
        for (auto current = m_head; current; previous = current, current = current->next)
        {
            if (node < current)
            {
                if (node->next = current; !previous)
                {
                    m_head = node; // note: move head to the left
                }
                else
                {
                    previous->next = node; // note: insert node
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

    [[nodiscard]] std::pair < Node * , Node * > find_first(std::size_t size) const // note: fast, bu fragmentation
    {
        Node * current = m_head, * previous = nullptr; // note: remember the second * here

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

	static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

    std::size_t m_size = 0;

    void * m_begin = nullptr;
    Node * m_head  = nullptr;

}; // class Block_Allocator : private boost::noncopyable

void test_1(benchmark::State & state) // note: pretty fast
{
	const std::size_t kb = 1024, mb = kb * kb, gb = kb * kb * kb;

    std::mt19937 engine(state.range(0));

    std::uniform_int_distribution distribution(1, 16);

    std::vector < void * > pointers(kb, nullptr);

	for (auto _ : state)
	{
		Block_Allocator allocator(16 * gb); // note: huge constant

		for (std::size_t i = 0; i < kb; i +=  1) pointers[i] = allocator.  allocate(distribution(engine) * mb);
		for (std::size_t i = 0; i < kb; i += 32)               allocator.deallocate(pointers[i]              );
		for (std::size_t i = 0; i < kb; i += 32) pointers[i] = allocator.  allocate(distribution(engine) * mb);
		for (std::size_t i = 0; i < kb; i +=  1)               allocator.deallocate(pointers[i]              );
	}
}

void test_2(benchmark::State & state) // note: pretty slow
{
	const std::size_t kb = 1024, mb = kb * kb;

    std::mt19937 engine(state.range(0));

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

BENCHMARK(test_1)->Arg(42); // note: same seeds for PRNG
BENCHMARK(test_2)->Arg(42);

int main(int argc, char ** argv) // note: arguments for benchmark
{
    Block_Allocator allocator(1024);                           allocator.print(); // note: initial

	[[maybe_unused]] auto ptr_A = allocator.  allocate(   16); allocator.print(); // note: initial + 32
	[[maybe_unused]] auto ptr_B = allocator.  allocate(   32); allocator.print(); // note: initial + 32 + 48
	[[maybe_unused]] auto ptr_C = allocator.  allocate(   32); allocator.print(); // note: initial + 32 + 48 + 48
    [[maybe_unused]] auto ptr_D = allocator.  allocate(   16); allocator.print(); // note: initial + 32 + 48 + 48 + 32

	                              allocator.deallocate(ptr_B); allocator.print(); // note: initial + 32
                                  allocator.deallocate(ptr_C); allocator.print(); // note: initial + 32

	[[maybe_unused]] auto ptr_E = allocator.  allocate(   16); allocator.print(); // note: initial + 32 + 32
	[[maybe_unused]] auto ptr_F = allocator.  allocate(   32); allocator.print(); // note: initial + 32 + 48 + 48 + 32
    
    // note: HAHBBHCCHDD -> HA000000HDD -> HAHEHFF0HDD, each letter states for 16 bytes if sizeof(Header) == 16

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}