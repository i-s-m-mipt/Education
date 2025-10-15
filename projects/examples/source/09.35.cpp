///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <format>
#include <iostream>
#include <memory>
#include <new>
#include <random>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

class Allocator : private boost::noncopyable
{
public :
	
    Allocator(std::size_t size) : m_size(size)
    {
        assert(m_size >= sizeof(Node) + 1);
        
        m_begin = operator new(m_size, std::align_val_t(s_alignment));

	    m_head = get_node(m_begin);
            
        m_head->size = m_size - sizeof(Header);
            
        m_head->next = nullptr;
    }

//  -----------------------------------------------------------------------------------------------
	
   ~Allocator()
    {
        operator delete(m_begin, m_size, std::align_val_t(s_alignment));
    }

//  -----------------------------------------------------------------------------------------------

    auto allocate(std::size_t size) -> void *
    {
	    void * end = get_byte(m_begin) + sizeof(Header) + size, * next = end;

	    auto free = 2 * alignof(Header);

        if (next = std::align(alignof(Header), sizeof(Header), next, free); next)
        {
            auto padding = get_byte(next) - get_byte(end);

            if (auto [current, previous] = find(size + padding); current)
            {
                if (current->size >= size + padding + sizeof(Node) + 1)
                {
                    auto step = sizeof(Header) + size + padding;

                    auto node = get_node(get_byte(current) + step);

                    node->size = current->size - step;
                       
                    node->next = current->next;
                    
                    current->next = node;
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

                auto header = get_header(current);
                
                header->size = size + padding;

                return get_byte(current) + sizeof(Header);
            }
        }

        return nullptr;
    }

//  -----------------------------------------------------------------------------------------------

    void deallocate(void * x)
    {
        auto node = get_node(get_byte(x) - sizeof(Header));

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

            previous = current;
            
            current  = current->next;
        }

        merge(previous, node);
    }

//  -----------------------------------------------------------------------------------------------

    void show() const
    { 
        std::cout << "Chain_Allocator::show : ";

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

private :

    struct Node 
    { 
        std::size_t size = 0;
        
        Node * next = nullptr;
    };

//  -----------------------------------------------------------------------------------------------

	struct alignas(std::max_align_t) Header 
    { 
        std::size_t size = 0;
    };

//  -----------------------------------------------------------------------------------------------

    auto get_byte(void * x) const -> std::byte *
	{
		return static_cast < std::byte * > (x);
	}

//  -----------------------------------------------------------------------------------------------

    auto get_node(void * x) const -> Node *
	{
		return static_cast < Node * > (x);
	}

//  -----------------------------------------------------------------------------------------------

    auto get_header(void * x) const -> Header *
	{
		return static_cast < Header * > (x);
	}

//  -----------------------------------------------------------------------------------------------

    auto find(std::size_t size) const -> std::pair < Node *, Node * >
    {
        Node * current = m_head, * previous = nullptr;

	    while (current && size > current->size)
        {
            previous = current;
            
            current  = current->next;
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

    void * m_begin = nullptr;
    
    Node * m_head  = nullptr;

//  -----------------------------------------------------------------------------------------------

    static inline auto s_alignment = alignof(std::max_align_t);
};

///////////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

    std::uniform_int_distribution distribution(1, 16);

    std::default_random_engine engine;

    std::vector < void * > vector(kb, nullptr);

	for (auto element : state)
	{
		Allocator allocator(16 * gb);

		for (auto i = 0uz; i < kb; ++i)
        { 
            vector[i] = allocator.allocate(distribution(engine) * mb);
        }

		for (auto i = 0uz; i < kb; i += 32)
        { 
            allocator.deallocate(vector[i]);
        }

		for (auto i = 0uz; i < kb; i += 32)
        { 
            vector[i] = allocator.allocate(distribution(engine) * mb);
        }

		for (auto i = 0uz; i < kb; ++i)
        { 
            allocator.deallocate(vector[i]);
        }
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb;

    std::uniform_int_distribution distribution(1, 16);

    std::default_random_engine engine;

    std::vector < std::pair < void *, std::size_t > > vector(kb);

	for (auto element : state)
	{
		for (auto i = 0uz; i < kb; ++i)
        {
            vector[i].second = distribution(engine) * mb;
            
            vector[i].first  = operator new(vector[i].second);
        }
        
		for (auto i = 0uz; i < kb; i += 32)
        {
            operator delete(vector[i].first, vector[i].second);
        }

		for (auto i = 0uz; i < kb; i += 32)
        {
            vector[i].second = distribution(engine) * mb;
            
            vector[i].first  = operator new(vector[i].second);
        } 
        
		for (auto i = 0uz; i < kb; ++i) 
        {
            operator delete(vector[i].first, vector[i].second);
        }
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Allocator allocator(1'024);

//  --------------------------------------------------
    
    allocator.show();          allocator.allocate(16); 
    
    allocator.show(); auto x = allocator.allocate(16); 
    
    allocator.show(); auto y = allocator.allocate(16); 
    
    allocator.show();          allocator.allocate(16);

//  --------------------------------------------------
    
    allocator.show(); allocator.deallocate(y);
    
    allocator.show(); allocator.deallocate(x);

//  --------------------------------------------------
    
    allocator.show(); auto z = allocator.allocate(32);
    
    allocator.show();

//  --------------------------------------------------

    assert(z == x);

//  --------------------------------------------------

    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////////////////////