#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

//  ================================================================================================

class Arena_Allocator : private boost::noncopyable
{
public:

	explicit Arena_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size, default_alignment);
	}

   ~Arena_Allocator() noexcept
	{
		::operator delete(m_begin, m_size, default_alignment);
	}

public:

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) noexcept
	{
		void * first = get_byte(m_begin) + m_offset;

		auto space = m_size - m_offset;

		if (first = std::align(alignment, size, first, space); first)
		{
			m_offset = m_size - space + size; 
			
			return first;
		}
		else return nullptr;
	}

	void print() const
	{
		std::cout << m_begin << ": ";

		std::cout << std::setw(4) << std::right << std::setfill('0') << m_offset;

		std::cout << " / " << m_size << std::endl;
	}

private:

	[[nodiscard]] std::byte * get_byte(void * ptr) const noexcept
	{
		return static_cast < std::byte * > (ptr);
	}

public:

	static constexpr std::align_val_t default_alignment { alignof(std::max_align_t) };

private:
	
	const std::size_t m_size;

private:

	std::size_t m_offset = 0;

	void * m_begin = nullptr;

}; // class Arena_Allocator : private boost::noncopyable

//  ================================================================================================

void test_1(benchmark::State & state)
{
	constexpr std::size_t kb = 1024, mb = kb * kb, gb = kb * kb * kb;

	for (auto _ : state)
	{
		Arena_Allocator allocator(gb);

		for (std::size_t i = 0; i < kb; ++i)
		{
			benchmark::DoNotOptimize(allocator.allocate(mb));
		}
	}
}

//  ================================================================================================

void test_2(benchmark::State & state)
{
	constexpr std::size_t kb = 1024, mb = kb * kb;

	std::vector < void * > pointers(kb, nullptr);

	for (auto _ : state)
	{
		for (std::size_t i = 0; i < kb; ++i) pointers[i] = ::operator    new(             mb);
		for (std::size_t i = 0; i < kb; ++i)               ::operator delete(pointers[i], mb);
	}
}

//  ================================================================================================

BENCHMARK(test_1);
BENCHMARK(test_2);

//  ================================================================================================

int main(int argc, char ** argv)
{
	Arena_Allocator allocator(1024); 

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