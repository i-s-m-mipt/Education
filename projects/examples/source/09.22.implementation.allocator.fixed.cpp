#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

//  ================================================================================================

template < auto N > class Fixed_Allocator : private boost::noncopyable
{
public:

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) noexcept
	{
		void * first = m_begin + m_offset;

		auto space = N - m_offset;

		if (first = std::align(alignment, size, first, space); first)
		{
			m_offset = N - space + size; 
			
			return first;
		}
		else return nullptr;
	}

	void print() const
	{
		std::cout << m_begin << ": ";

		std::cout << std::setw(4) << std::right << std::setfill('0') << m_offset;

		std::cout << " / " << N << std::endl;
	}

private:
	
	std::size_t m_offset = 0;

    alignas(std::max_align_t) std::byte m_buffer[N];

    std::byte * m_begin = m_buffer;

}; // class Fixed_Allocator : private boost::noncopyable

//  ================================================================================================

void test_1(benchmark::State & state)
{
	constexpr std::size_t kb = 1024, mb = kb * kb;

	for (auto _ : state)
	{
		Fixed_Allocator < mb > allocator;

		for (std::size_t i = 0; i < kb; ++i)
		{
			benchmark::DoNotOptimize(allocator.allocate(kb));
		}
	}
}

//  ================================================================================================

void test_2(benchmark::State & state)
{
	constexpr std::size_t kb = 1024;

	std::vector < void * > pointers(kb, nullptr);

	for (auto _ : state)
	{
		for (std::size_t i = 0; i < kb; ++i) pointers[i] = ::operator new   (kb         );
		for (std::size_t i = 0; i < kb; ++i)               ::operator delete(pointers[i]);
	}
}

//  ================================================================================================

BENCHMARK(test_1);
BENCHMARK(test_2);

//  ================================================================================================

int main(int argc, char ** argv)
{
	Fixed_Allocator < 1024 > allocator; 

	std::cout << allocator.allocate(  1, 4) << ' '; allocator.print(); // detail: A
	std::cout << allocator.allocate(  2, 2) << ' '; allocator.print(); // detail: B
	std::cout << allocator.allocate( 10   ) << ' '; allocator.print(); // detail: C
	std::cout << allocator.allocate(  4   ) << ' '; allocator.print(); // detail: D

	// detail: A0BB 0000 | CCCC CCCC | CC00 0000 | DDDD 0000 | ...

	std::cout << allocator.allocate(988   ) << ' '; allocator.print();
	std::cout << allocator.allocate(  1   ) << ' '; allocator.print(); // detail: 0

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}