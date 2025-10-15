//////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <format>
#include <iostream>
#include <memory>
#include <new>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

//////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////////////////////////////

class Allocator : private boost::noncopyable
{
public :

	Allocator(std::size_t size) : m_size(size)
	{
		m_begin = operator new(m_size, std::align_val_t(s_alignment));
	}

//  ------------------------------------------------------------------------------

   ~Allocator()
	{
		operator delete(m_begin, m_size, std::align_val_t(s_alignment));
	}

//  ------------------------------------------------------------------------------

	auto allocate(std::size_t size, std::size_t alignment = s_alignment) -> void *
	{
		void * begin = get_byte(m_begin) + m_offset;

		auto free = m_size - m_offset;

		if (begin = std::align(alignment, size, begin, free); begin)
		{
			m_offset = m_size - free + size;
			
			return begin;
		}
		else 
		{
			return nullptr;
		}
	}

//  ------------------------------------------------------------------------------

	void show() const
	{
		std::cout << "Allocator::show : m_size = " << m_size << ' ';

		std::cout << "m_begin = "  << std::format("{:018}", m_begin) << ' ';

		std::cout << "m_offset = " << std::format("{:0>4}", m_offset) << '\n';
	}

private :

	auto get_byte(void * x) const -> std::byte *
	{
		return static_cast < std::byte * > (x);
	}

//  ------------------------------------------------------------------------------

	std::size_t m_size = 0, m_offset = 0;
	
	void * m_begin = nullptr;

//  ------------------------------------------------------------------------------

	static inline auto s_alignment = alignof(std::max_align_t);
};

//////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

	for (auto element : state)
	{
		Allocator allocator(gb);

		for (auto i = 0uz; i < kb; ++i)
		{
			benchmark::DoNotOptimize(allocator.allocate(mb));
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////

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

		for (auto i = 0uz; i < kb; ++i) 
		{ 
			operator delete(vector[i], mb);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

//////////////////////////////////////////////////////////////////////////////////

int main()
{
	Allocator allocator(1'024);

//  -------------------------------------------

	allocator.show(); allocator.allocate(1, 1);

	allocator.show(); allocator.allocate(2, 2); 
	
	allocator.show(); allocator.allocate(4, 4); 
	
	allocator.show(); allocator.allocate(8, 8); 
	
	allocator.show();

//  -------------------------------------------

    benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////////////////////////////////////////