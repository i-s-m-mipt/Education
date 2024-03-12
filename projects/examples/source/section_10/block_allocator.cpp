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

    struct Node { std::size_t size = 0; Node * next = nullptr; };

	struct alignas(std::max_align_t) Header { std::size_t size = 0; };

public:
	
    explicit Block_Allocator(std::size_t size) : m_size(size)
    {
        if (m_size >= sizeof(Node) + 1) 
        {
            m_begin = ::operator new(m_size, default_alignment);

	        m_head = get_node(m_begin); 
        
            m_head->size = m_size - sizeof(Header);
        }
        else throw std::runtime_error("invalid size");
    }
	
    ~Block_Allocator() noexcept
    {
        ::operator delete(m_begin, m_size, default_alignment);
    }

    [[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) noexcept
    {
        if (size >= sizeof(Node))
        {
	        void * last = get_byte(m_begin) + sizeof(Header) + size, * next = last;

	        auto space = 2 * alignof(Header); // note: enough space to align next pointer to Header

            if (next = std::align(alignof(Header), sizeof(Header), next, space); next) // note: modifies next and space
            {
                auto padding = get_byte(next) - get_byte(last);

                if (auto [current, previous] = find_first(size + padding); current != nullptr) // note: or find best
                {
                    if (current->size >= size + padding + sizeof(Node*) + 1)
                    {
                        auto splitted_node = get_node(get_byte(current) + sizeof(Header) + size + padding);

                        splitted_node->size = current->size - (sizeof(Header) + size + padding);
                        
                        splitted_node->next = current->next; current->next = splitted_node;
                    }
                    else
                    {
                        padding += current->size - (size + padding);
                    }

                    if (previous == nullptr)
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
                else return nullptr;
            }
            else return nullptr;
        }
        else return nullptr;
    }

    void deallocate(void * ptr) noexcept;

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
        Node * c = m_head, * p = nullptr; // note: remember the second * here

	    for (; c && size > c->size; p = c, c = c->next) {}

        return std::make_pair(c, p);
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

    void * m_begin = nullptr;
    Node * m_head  = nullptr;

}; // class Block_Allocator : private boost::noncopyable