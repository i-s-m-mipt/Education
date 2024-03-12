#include <bit>
#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

class Block_Allocator : private boost::noncopyable // note: deallocations at any position for blocks of different sizes
{
private:

    struct List
	{
		struct Node { std::size_t size = 0; Node * next = nullptr; };

		void find_first(std::size_t s, Node * & c, Node * & p) const noexcept // note: or find_best
        {
	        for (c = head, p = nullptr; c != nullptr && s > c->size; p = c, c = c->next) {}
        }

        Node * head = nullptr;

	}; // struct List

    using Node = List::Node;

	struct alignas(std::max_align_t) Header { std::size_t m_size = 0; };

public:
	
    explicit Block_Allocator(std::size_t size) : m_size(size)
    {
        if (m_size < sizeof(Node) + 1)
		{
			throw std::runtime_error("invalid size");
		}

	    m_begin = ::operator new(m_size, default_alignment);

	    m_list.head = get_node(m_begin); 
        
        m_list.head->size = m_size - sizeof(Header);
    }
	
    ~Block_Allocator() noexcept
    {
        ::operator delete(m_begin, m_size, default_alignment);
    }

    [[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) noexcept;

    void deallocate(void * ptr) noexcept;

private:

    std::byte * get_byte(void * ptr) const noexcept
	{
		return std::bit_cast < std::byte * > (ptr);
	}

    Node * get_node(void * ptr) const noexcept
	{
		return std::bit_cast < Node * > (ptr);
	}

	void Coalescence(Node* prev, Node* curr)
    {
	    if (curr->next != nullptr && (std::size_t)curr + curr->size + sizeof(Header) == (std::size_t)curr->next)
	    {
		    curr->size += curr->next->size + sizeof(Header);
		    curr->next = curr->next->next;
	    }

	    if (prev != nullptr && (std::size_t)prev + prev->size + sizeof(Header) == (std::size_t)curr)
	    {
		    prev->size += curr->size + sizeof(Header);
		    prev->next = curr->next;
	    }
    }

public:

	static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

    std::size_t m_size = 0;

    List m_list;

    void * m_begin = nullptr;

}; // class Block_Allocator : private boost::noncopyable