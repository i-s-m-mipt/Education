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

    struct Node 
    { 
        std::size_t size = 0; Node * next = nullptr; 
    };

	struct alignas(std::max_align_t) Header 
    { 
        std::size_t size = 0; 
    };

public:
	
    explicit Block_Allocator(std::size_t size) : m_size(size)
    {
        if (m_size >= sizeof(Node) + 1) 
        {
            m_begin = operator new(m_size, std::align_val_t(default_alignment));

	        m_head = get_node(m_begin); 
            
            m_head->size = m_size - sizeof(Header);
            
            m_head->next = nullptr;
        }
        else 
        {
            throw std::runtime_error("invalid size");
        }
    }
	
   ~Block_Allocator()
    {
        if (m_begin)
        {
            operator delete(m_begin, m_size, std::align_val_t(default_alignment));
        }
    }

public:

    void * allocate(std::size_t size)
    {
	    void * end = get_byte(m_begin) + sizeof(Header) + size, * next = end;

	    auto space = 2 * alignof(Header);

        if (next = std::align(alignof(Header), sizeof(Header), next, space); next)
        {
            auto padding = get_byte(next) - get_byte(end);

            if (auto [current, previous] = find_first(size + padding); current)
            {
                if (current->size >= size + padding + sizeof(Node) + 1)
                {
                    auto block_size = sizeof(Header) + size + padding;

                    auto node = get_node(get_byte(current) + block_size);

                    node->size = current->size - block_size;
                       
                    node->next = current->next; current->next = node;
                }
                else
                {
                    padding += current->size - size - padding;
                }

                if (!previous)
                {
                    m_head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                auto header = get_header(current); header->size = size + padding;

                return get_byte(current) + sizeof(Header);
            }
        }

        return nullptr;
    }

    void deallocate(void * ptr)
    {
        auto node = get_node(get_byte(ptr) - sizeof(Header));

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

    std::byte * get_byte(void * ptr) const
	{
		return static_cast < std::byte * > (ptr);
	}

    Node * get_node(void * ptr) const
	{
		return static_cast < Node * > (ptr);
	}

    Header * get_header(void * ptr) const
	{
		return static_cast < Header * > (ptr);
	}

    std::pair < Node * , Node * > find_first(std::size_t size) const
    {
        Node * current = m_head, * previous = nullptr;

	    for (; current && size > current->size; previous = current, current = current->next);

        return std::make_pair(current, previous);
    }

	void merge(Node * previous, Node * node) const
    {
	    if (node->next && get_byte(node) + sizeof(Header) + node->size == get_byte(node->next))
	    {
		    node->size += sizeof(Header) + node->next->size;

		    node->next = node->next->next;
	    }

	    if (previous && get_byte(previous) + sizeof(Header) + previous->size == get_byte(node))
	    {
		    previous->size += sizeof(Header) + node->size;

		    previous->next = node->next;
	    }
    }

private:

	static inline auto default_alignment = alignof(std::max_align_t);

//  -----------------------------------------------------------------

    std::size_t m_size = 0;

    void * m_begin = nullptr;
    Node * m_head  = nullptr;
};

//  ================================================================================================

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

    std::mt19937_64 engine(state.range(0));

    std::uniform_int_distribution distribution(1, 16);

    std::vector < void * > ptrs(kb, nullptr);

	for (auto value : state)
	{
		Block_Allocator allocator(16 * gb);

		for (auto i = 0uz; i < kb; ++i) 
        { 
            ptrs[i] = allocator.allocate(distribution(engine) * mb); 
        }

		for (auto i = 0uz; i < kb; i += 32) 
        { 
            allocator.deallocate(ptrs[i]); 
        }

		for (auto i = 0uz; i < kb; i += 32) 
        { 
            ptrs[i] = allocator.allocate(distribution(engine) * mb); 
        }

		for (auto i = 0uz; i < kb; ++i) 
        { 
            allocator.deallocate(ptrs[i]); 
        }
	}
}

//  ================================================================================================

void test_v2(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb;

    std::mt19937_64 engine(state.range(0));

    std::uniform_int_distribution distribution(1, 16);

    std::vector < std::pair < void * , std::size_t > > blocks(kb);

	for (auto value : state)
	{
		for (auto i = 0uz; i < kb; ++i) 
        {
            auto size = distribution(engine) * mb; 
            
            blocks[i].first = operator new(size); blocks[i].second = size;
        }
        
		for (auto i = 0uz; i < kb; i += 32) 
        {
            operator delete(blocks[i].first, blocks[i].second);
        }

		for (auto i = 0uz; i < kb; i += 32)
        {
            auto size = distribution(engine) * mb; 
            
            blocks[i].first = operator new(size); blocks[i].second = size;
        } 
        
		for (auto i = 0uz; i < kb; ++i) 
        {
            operator delete(blocks[i].first, blocks[i].second);
        }
	}
}

//  ================================================================================================

BENCHMARK(test_v1)->Arg(42);
BENCHMARK(test_v2)->Arg(42);

//  ================================================================================================

int main(int argc, char ** argv)
{
    Block_Allocator allocator(1'024);
    
    allocator.print(); 

	[[maybe_unused]] auto ptr_1 = allocator.allocate(16); allocator.print();
	[[maybe_unused]] auto ptr_2 = allocator.allocate(32); allocator.print();
	[[maybe_unused]] auto ptr_3 = allocator.allocate(32); allocator.print();
    [[maybe_unused]] auto ptr_4 = allocator.allocate(16); allocator.print();

	allocator.deallocate(ptr_2); allocator.print();
    allocator.deallocate(ptr_3); allocator.print();

	[[maybe_unused]] auto ptr_5 = allocator.allocate(16); allocator.print();
	[[maybe_unused]] auto ptr_6 = allocator.allocate(32); allocator.print();
    
    // detail: H1H5H660H44

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();
}