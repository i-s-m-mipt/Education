#include <cstddef>
#include <exception>
#include <format>
#include <iostream>
#include <memory>
#include <new>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

class Block_Allocator : private boost::noncopyable
{
public:
	
    Block_Allocator(std::size_t size) : m_size(size)
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

//  -----------------------------------------------------------------------------------------------

    auto allocate(std::size_t size) -> void *
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

        Node * previous = nullptr, * current = m_head;
        
        while (current)
        {
            if (node < current)
            {
                node->next = current;
                
                if (!previous)
                {
                    m_head = node;
                }
                else
                {
                    previous->next = node;
                }

                break;
            }

            previous = current; current = current->next;
        }

        merge(previous, node);
    }

//  -----------------------------------------------------------------------------------------------

    void test() const
    { 
        std::cout << "Chain_Allocator::test : ";

        std::cout << "m_size = "  << m_size << ' ';

        std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';

        std::cout << "m_head = "  << std::format("{:018}", static_cast < void * > (m_head)) << ' '; 

        if (m_head->next)
        {
            std::cout << "m_head->next = ";
            
            std::cout << std::format("{:018}", static_cast < void * > (m_head->next));
        }

        std::cout << '\n';
    }

private:

    struct Node 
    { 
        std::size_t size = 0; Node * next = nullptr; 
    };

//  -----------------------------------------------------------------------------------------------

	struct alignas(std::max_align_t) Header 
    { 
        std::size_t size = 0; 
    };

//  -----------------------------------------------------------------------------------------------

    auto get_byte(void * ptr) const -> std::byte *
	{
		return static_cast < std::byte * > (ptr);
	}

    auto get_node(void * ptr) const -> Node *
	{
		return static_cast < Node * > (ptr);
	}

    auto get_header(void * ptr) const -> Header *
	{
		return static_cast < Header * > (ptr);
	}

//  -----------------------------------------------------------------------------------------------

    auto find_first(std::size_t size) const -> std::pair < Node * , Node * >
    {
        Node * current = m_head, * previous = nullptr;

	    while (current && size > current->size)
        {
            previous = current; current = current->next;
        }

        return std::make_pair(current, previous);
    }

//  -----------------------------------------------------------------------------------------------

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

//  -----------------------------------------------------------------------------------------------

    std::size_t m_size = 0;

    void * m_begin = nullptr; Node * m_head = nullptr;

//  -----------------------------------------------------------------------------------------------

    static inline auto default_alignment = alignof(std::max_align_t);
};

///////////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

    std::default_random_engine engine;

    std::uniform_int_distribution distribution(1, 16);

    std::vector < void * > ptrs(kb, nullptr);

	for (auto element : state)
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

///////////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb;

    std::default_random_engine engine;

    std::uniform_int_distribution distribution(1, 16);

    std::vector < std::pair < void * , std::size_t > > blocks(kb);

	for (auto element : state)
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

///////////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);
BENCHMARK(test_v2);

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Block_Allocator allocator(1'024);
    
    allocator.test(); 

	[[maybe_unused]] auto ptr_1 = allocator.allocate(1); allocator.test();

	[[maybe_unused]] auto ptr_2 = allocator.allocate(2); allocator.test();

	[[maybe_unused]] auto ptr_3 = allocator.allocate(3); allocator.test();

    [[maybe_unused]] auto ptr_4 = allocator.allocate(4); allocator.test();

	allocator.deallocate (ptr_3);                        allocator.test();
    
    allocator.deallocate (ptr_2);                        allocator.test();

	[[maybe_unused]] auto ptr_5 = allocator.allocate(5); allocator.test();

//  ----------------------------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}