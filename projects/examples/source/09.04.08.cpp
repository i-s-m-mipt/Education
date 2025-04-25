////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <format>
#include <iostream>
#include <new>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

class Allocator : private boost::noncopyable
{
public :

	Allocator(std::size_t size, std::size_t step) : m_size(size), m_step(step)
	{
		assert(m_size % m_step == 0 && m_step >= sizeof(Node));

		make_list();
			
		m_begin = m_head;
	}

//  ------------------------------------------------------------------------------------------------

   ~Allocator()
	{
		for (auto list : m_lists) 
		{
			if (list)
			{
				operator delete(list, m_size, std::align_val_t(s_alignment));
			}
		}
	}

//  ------------------------------------------------------------------------------------------------

	auto allocate() -> void *
	{
		if (!m_head)
		{
			if (m_offset == std::size(m_lists))
			{
				make_list();
			}
			else 
			{
				m_head = get_node(m_lists[++m_offset - 1]);
			}
		}

		auto node = m_head;

		if (!node->next)
		{
			auto next = get_byte(node) + m_step;

			if (next != get_byte(m_lists[m_offset - 1]) + m_size)
			{
				m_head = get_node(next);
				
				m_head->next = nullptr;
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

//  ------------------------------------------------------------------------------------------------

	void deallocate(void * x)
	{
		auto node = get_node(x);
		
		node->next = m_head;
		
		m_head = node;
	}

//  ------------------------------------------------------------------------------------------------

	void test() const
	{ 
		std::cout << "Allocator::test : ";

		std::cout << "m_size = "   << m_size << ' ' << "m_step = " << m_step << ' ';

		std::cout << "m_begin = "  << std::format("{:018}", m_begin) << ' ';

		std::cout << "m_head = "   << std::format("{:018}", static_cast < void * > (m_head)) << ' ';

		std::cout << "m_offset = " << m_offset << '\n';
	}

private :

	struct Node 
	{ 
		Node * next = nullptr;
	};

//  ------------------------------------------------------------------------------------------------

	auto get_byte(void * x) const -> std::byte *
	{
		return static_cast < std::byte * > (x);
	}

//  ------------------------------------------------------------------------------------------------

	auto get_node(void * x) const -> Node *
	{ 
		return static_cast < Node * > (x);
	}

//  ------------------------------------------------------------------------------------------------

	auto allocate_nodes() const
	{
		auto node = get_node(operator new(m_size, std::align_val_t(s_alignment)));
		
		node->next = nullptr;
		
		return node;
	}

//  ------------------------------------------------------------------------------------------------

	void make_list()
	{
		m_head = allocate_nodes();
		
		++m_offset;
		
		m_lists.push_back(m_head);
	}

//  ------------------------------------------------------------------------------------------------

	std::size_t m_size = 0, m_step = 0, m_offset = 0;

	void * m_begin = nullptr;
	
	Node * m_head  = nullptr;

	std::vector < void * > m_lists;

//  ------------------------------------------------------------------------------------------------

	static inline auto s_alignment = alignof(std::max_align_t);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

	std::vector < void * > vector(kb, nullptr);

	for (auto element : state)
	{
		Allocator allocator(gb, mb);

		for (auto i = 0uz; i < kb; ++i)
		{ 
			vector[i] = allocator.allocate();
		}

		for (auto i = 0uz; i < kb; i += 2)
		{ 
			allocator.deallocate(vector[i]);
		}

		for (auto i = 0uz; i < kb; i += 2)
		{ 
			vector[i] = allocator.allocate();
		}

		for (auto i = 0uz; i < kb; ++i)
		{ 
			allocator.deallocate(vector[i]);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb;

	std::vector < void * > vector(kb, nullptr);

	for (auto element : state)
	{
		for (auto i = 0uz; i < kb; ++i)
		{ 
			vector[i] = operator new(mb);
		}

		for (auto i = 0uz; i < kb; i += 2)
		{
			operator delete(vector[i], mb);
		}

		for (auto i = 0uz; i < kb; i += 2)
		{
			vector[i] = operator new(mb);
		}

		for (auto i = 0uz; i < kb; ++i)
		{ 
			operator delete(vector[i], mb);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Allocator allocator(32, 8);

//  ------------------------------------------------
	
	allocator.test();          allocator.allocate(); 
	
	allocator.test(); auto x = allocator.allocate(); 
	
	allocator.test(); auto y = allocator.allocate(); 
	
	allocator.test();          allocator.allocate(); 
	
	allocator.test();          allocator.allocate();

//  ------------------------------------------------
	
	allocator.test(); allocator.deallocate(x);
	
	allocator.test(); allocator.deallocate(y);

//  ------------------------------------------------
	
	allocator.test(); auto z = allocator.allocate();
	
	allocator.test();

//  ------------------------------------------------

	assert(z == y);

//  ------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////////////////////////////////////////////////////////////////