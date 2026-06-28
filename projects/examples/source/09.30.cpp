///////////////////////////////////////////////////////////////////////////////////////

// chapter : Memory

///////////////////////////////////////////////////////////////////////////////////////

// content : List Allocator
//
// content : Microbenchmarking

///////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <iterator>
#include <new>
#include <print>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////

class Allocator
{
public :

	Allocator(std::size_t size, std::size_t step) : m_size(size), m_step(step)
	{
		assert(m_size % m_step == 0 && m_step >= sizeof(Node));

		make_array();

		m_array = m_head;
	}

//  -----------------------------------------------------------------------------------

   ~Allocator()
	{
		for (auto array : m_arrays)
		{
			operator delete(array, m_size, std::align_val_t(s_alignment));
		}
	}

//  -----------------------------------------------------------------------------------

	auto allocate() -> void *
	{
		if (!m_head)
		{
			if (m_offset == std::size(m_arrays))
			{
				make_array();
			}
			else
			{
				m_head = get_node(m_arrays[++m_offset - 1]);
			}
		}

		auto node = m_head;

		if (!node->next)
		{
			auto next = get_byte(node) + m_step;

			if (next != get_byte(m_arrays[m_offset - 1]) + m_size)
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

//  -----------------------------------------------------------------------------------

	void deallocate(void * x)
	{
		auto node = get_node(x);

		node->next = m_head;

		m_head = node;
	}

//  -----------------------------------------------------------------------------------

	void show() const
	{
		std::print("Allocator::show : ");

		std::print
		(
			"m_array = {:018} m_size = {} m_step = {} m_offset = {} m_head = {:018}\n",

			m_array, m_size, m_step, m_offset, static_cast < void * > (m_head)
		);
	}

private :

	struct Node
	{
		Node * next = nullptr;
	};

//  -----------------------------------------------------------------------------------

	auto get_byte(void * x) const -> std::byte *
	{
		return static_cast < std::byte * > (x);
	}

//  -----------------------------------------------------------------------------------

	auto get_node(void * x) const -> Node *
	{
		return static_cast < Node * > (x);
	}

//  -----------------------------------------------------------------------------------

	void make_array()
	{
		m_head = get_node(operator new(m_size, std::align_val_t(s_alignment)));

		m_head->next = nullptr;

		++m_offset;

		m_arrays.push_back(m_head);
	}

//  -----------------------------------------------------------------------------------

	void * m_array = nullptr;

	std::size_t m_size = 0, m_step = 0, m_offset = 0;

	Node * m_head = nullptr;

	std::vector < void * > m_arrays;

//  -----------------------------------------------------------------------------------

	static inline auto s_alignment = alignof(std::max_align_t);
};

///////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1uz << 10, mb = 1uz << 20;

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

		benchmark::DoNotOptimize(vector);
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	auto kb = 1uz << 10, mb = 1uz << 20, gb = 1uz << 30;

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

		benchmark::DoNotOptimize(vector);
	}
}

///////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Allocator allocator(32, 8);

//  ------------------------------------------------

	allocator.show();          allocator.allocate();

	allocator.show(); auto x = allocator.allocate();

	allocator.show(); auto y = allocator.allocate();

	allocator.show();          allocator.allocate();

	allocator.show();          allocator.allocate();

//  ------------------------------------------------

	allocator.show(); allocator.deallocate(x);

	allocator.show(); allocator.deallocate(y);

//  ------------------------------------------------

	allocator.show(); auto z = allocator.allocate();

	allocator.show();

//  ------------------------------------------------

	assert(z == y);

//  ------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////////