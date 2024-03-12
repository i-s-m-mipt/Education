#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <iterator>
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

    struct List
	{
		struct Node { std::size_t size = 0; Node * next = nullptr; };

		std::pair < Node * , Node * > find_first(std::size_t size) const noexcept
        {
            Node * c = head, * p = nullptr; // note: remember the second * here

	        for (; c && size > c->size; p = c, c = c->next) {}

            return std::make_pair(c, p);
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

    [[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) noexcept
    {
	std::size_t padding;
	void* currentAddress = (void*)(sizeof(Header) + size);
	void* nextAddress = (void*)(sizeof(Header) + size);
	std::size_t space = size + 100;
	std::align(alignof(std::max_align_t), sizeof(std::max_align_t), nextAddress, space);
	padding = (std::size_t)nextAddress - (std::size_t)currentAddress;

	LinkedList::Node* prev;
	LinkedList::Node* best;

	switch (m_SearchMethod)
	{
	case SearchMethod::FIRST:
		m_List.SearchFirst(size + padding, best, prev);
		break;
	case SearchMethod::BEST:
		m_List.SearchBest(size + padding, best, prev);
		break;
	}

	if (best == nullptr)
	{
		return nullptr;
	}

	if (best->m_Value >= size + padding + sizeof(LinkedList::Node*) + 1)
	{
		LinkedList::Node* splittedNode = reinterpret_cast<LinkedList::Node*>(reinterpret_cast<char*>(best) + sizeof(Header) + size + padding);
		splittedNode->m_Value = best->m_Value - (size + padding + sizeof(Header));
		splittedNode->m_Next = best->m_Next;
		best->m_Next = splittedNode;
	}
	else
	{
		padding += best->m_Value - (size + padding);
	}

	if (prev == nullptr)
	{
		m_List.m_Head = best->m_Next;
	}
	else
	{
		prev->m_Next = best->m_Next;
	}

	Header* header = reinterpret_cast<Header*>(best);
	header->m_Size = size + padding;

	return reinterpret_cast<char*>(best) + sizeof(Header);
}

    void deallocate(void * ptr) noexcept;

private:

    std::byte * get_byte(void * ptr) const noexcept
	{
		return static_cast < std::byte * > (ptr);
	}

    Node * get_node(void * ptr) const noexcept
	{
		return static_cast < Node * > (ptr);
	}

	void merge(Node* prev, Node* curr)
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