#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

//  ================================================================================================

template < std::size_t S > class Fixed_Allocator : private boost::noncopyable
{
public:

	void * allocate(std::size_t size, std::size_t alignment = default_alignment)
	{
		void * first = m_begin + m_offset;

		auto space = S - m_offset;

		if (first = std::align(alignment, size, first, space); first)
		{
			m_offset = S - space + size; 
			
			return first;
		}
		else 
		{
			return nullptr;
		}
	}

	void print() const
	{
		std::cout << m_begin << " : ";

		std::cout << std::setw(4) << std::setfill('0') << std::right << m_offset;

		std::cout << " / " << S << std::endl;
	}

private:

	static inline auto default_alignment = alignof(std::max_align_t);

//  -----------------------------------------------------------------
	
	std::size_t m_offset = 0;

    alignas(std::max_align_t) std::byte m_buffer[S]{};

    std::byte * m_begin = m_buffer;
};

//  ================================================================================================

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz;

	for (auto value : state)
	{
		Fixed_Allocator < 1'024 * 1'024 > allocator;

		for (auto i = 0uz; i < kb; ++i)
		{
			benchmark::DoNotOptimize(allocator.allocate(kb));
		}
	}
}

//  ================================================================================================

void test_v2(benchmark::State & state)
{
	auto kb = 1'024uz;

	std::vector < void * > ptrs(kb, nullptr);

	for (auto value : state)
	{
		for (auto i = 0uz; i < kb; ++i) 
		{
			ptrs[i] = operator new(kb);
		}

		for (auto i = 0uz; i < kb; ++i) 
		{
			operator delete(ptrs[i]);
		}
	}
}

//  ================================================================================================

BENCHMARK(test_v1);
BENCHMARK(test_v2);

//  ================================================================================================

int main(int argc, char ** argv)
{
	Fixed_Allocator < 1024 > allocator; 

	allocator.print();

	[[maybe_unused]] auto ptr_1 = allocator.allocate(  1, 4); allocator.print();
	[[maybe_unused]] auto ptr_2 = allocator.allocate(  2, 2); allocator.print();
	[[maybe_unused]] auto ptr_3 = allocator.allocate( 10   ); allocator.print();
	[[maybe_unused]] auto ptr_4 = allocator.allocate(  4   ); allocator.print();
	[[maybe_unused]] auto ptr_5 = allocator.allocate(988   ); allocator.print();
	[[maybe_unused]] auto ptr_6 = allocator.allocate(  1   ); allocator.print();

	// detail: 1022 0000 | 3333 3333 | 3300 0000 | 4444 0000 | 5555 5555 | ...	

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();
}