#include <cstddef>
#include <exception>
#include <format>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>
#include <vector>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

class Chain_Allocator : private boost::noncopyable
{
public:

	explicit Chain_Allocator(std::size_t size, std::size_t size_node) 
	: 
		m_size(size), m_size_node(size_node)
	{
		if (m_size % m_size_node == 0 && m_size_node >= sizeof(Node))
		{
			make_chain(); m_begin = m_head;
		}
		else 
		{
			throw std::runtime_error("invalid size");
		}
	}

   ~Chain_Allocator()
	{
		for (auto chain : m_chains) 
		{
			if (chain)
			{
				operator delete(chain, m_size, std::align_val_t(default_alignment));
			}
		}
	}

//  -----------------------------------------------------------------------------------------------

	auto allocate() -> void *
	{
		if (m_head == nullptr)
		{
			if (m_offset == std::size(m_chains))
			{
				make_chain();
			}
			else 
			{
				m_head = get_node(m_chains[++m_offset - 1]);
			}
		}

		auto node = m_head;

		if (!node->next)
		{
			auto next = get_byte(node) + m_size_node;

			if (next != get_byte(m_chains[m_offset - 1]) + m_size)
			{
				m_head = get_node(next); m_head->next = nullptr;
			}
			else 
			{
				m_head = m_head->next;
			}
		}
		else 
		{
			m_head = m_head->next;
		}

		return node;
	}

	void deallocate(void * ptr)
	{
		auto node = get_node(ptr); 
		
		node->next = m_head; m_head = node;
	}

//  -----------------------------------------------------------------------------------------------

	void test() const
	{ 
		std::cout << "Chain_Allocator::test : ";

		std::cout << "m_size = " << m_size << ' ' << "m_size_node = " << m_size_node << ' ';

		std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';

		std::cout << "m_head = "  << std::format("{:018}", static_cast < void * > (m_head)) << ' '; 

		std::cout << "m_offset = " << m_offset << '\n';
	}

private:

	struct Node 
	{ 
		Node * next = nullptr; 
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

//  -----------------------------------------------------------------------------------------------

	auto allocate_nodes() const
	{
		auto node = get_node(operator new(m_size, std::align_val_t(default_alignment)));
		
		node->next = nullptr; 
		
		return node;
	}

	void make_chain()
	{
		m_head = allocate_nodes(); ++m_offset; m_chains.push_back(m_head);
	}

//  -----------------------------------------------------------------------------------------------

	std::size_t m_size = 0, m_size_node = 0, m_offset = 0;

	void * m_begin = nullptr; Node * m_head = nullptr;

	std::vector < void * > m_chains;

//  -----------------------------------------------------------------------------------------------

	static inline auto default_alignment = alignof(std::max_align_t);
};

///////////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

	std::vector < void * > ptrs(kb, nullptr);

	for (auto value : state)
	{
		Chain_Allocator allocator(gb, mb);

		for (auto i = 0uz; i < kb; ++i) 
		{ 
			ptrs[i] = allocator.allocate(); 
		}

		for (auto i = 0uz; i < kb; i += 2) 
		{ 
			allocator.deallocate(ptrs[i]); 
		}

		for (auto i = 0uz; i < kb; i += 2) 
		{ 
			ptrs[i] = allocator.allocate(); 
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

	std::vector < void * > ptrs(kb, nullptr);

	for (auto value : state)
	{
		for (auto i = 0uz; i < kb; ++i) 
		{ 
			ptrs[i] = operator new(mb); 
		}

		for (auto i = 0uz; i < kb; i += 2) 
		{ 
			operator delete(ptrs[i], mb); 
		}

		for (auto i = 0uz; i < kb; i += 2) 
		{ 
			ptrs[i] = operator new(mb);
		}

		for (auto i = 0uz; i < kb; ++i) 
		{ 
			operator delete(ptrs[i], mb); 
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);
BENCHMARK(test_v2);

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Chain_Allocator allocator(32, 8);
	
	allocator.test();

	[[maybe_unused]] auto ptr_1 = allocator.allocate(); allocator.test();
	[[maybe_unused]] auto ptr_2 = allocator.allocate(); allocator.test();
	[[maybe_unused]] auto ptr_3 = allocator.allocate(); allocator.test();
	[[maybe_unused]] auto ptr_4 = allocator.allocate(); allocator.test();
	[[maybe_unused]] auto ptr_5 = allocator.allocate(); allocator.test();

	allocator.deallocate (ptr_2);                       allocator.test();
	allocator.deallocate (ptr_3);                       allocator.test();

	[[maybe_unused]] auto ptr_6 = allocator.allocate(); allocator.test();

//  ---------------------------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}