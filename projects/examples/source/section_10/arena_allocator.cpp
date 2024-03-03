#include <bit>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>

#include <boost/noncopyable.hpp>
#include <benchmark/benchmark.h>

class Arena_Allocator : private boost::noncopyable // note: no deallocations for blocks of different sizes
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

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) noexcept
	{
		void * first = get_byte(m_begin) + m_offset;

		auto space = m_size - m_offset;

		if (first = std::align(alignment, size, first, space); first) // note: modifies first and space
		{
			m_offset = m_size - space + size; 
			
			return first; // note: aligned pointer
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

	std::byte * get_byte(void * ptr) const noexcept
	{
		return std::bit_cast < std::byte * > (ptr);
	}

public:

	static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:
	
	std::size_t m_size   = 0;
	std::size_t m_offset = 0;

	void * m_begin = nullptr;

}; // class Arena_Allocator : private boost::noncopyable

void test_1(benchmark::State & state) // note: very fast
{
	const std::size_t kb = 1024, mb = kb * kb, gb = kb * kb * kb;

	for (auto _ : state)
	{
		Arena_Allocator allocator(gb);

		for (std::size_t i = 0; i < kb; ++i)
		{
			auto ptr = allocator.allocate(mb); benchmark::DoNotOptimize(ptr);
		}
	}
}

void test_2(benchmark::State & state) // note: very slow
{
	const std::size_t kb = 1024, mb = kb * kb;

	std::vector < void * > pointers(kb, nullptr);

	for (auto _ : state)
	{
		for (std::size_t i = 0; i < kb; ++i) pointers[i] = ::operator    new(             mb);
		for (std::size_t i = 0; i < kb; ++i)               ::operator delete(pointers[i], mb);
	}
}

BENCHMARK(test_1);
BENCHMARK(test_2);

int main(int argc, char ** argv) // note: arguments for benchmark
{
	Arena_Allocator allocator(1024); 

	std::cout << allocator.allocate(  1, 4) << ' '; allocator.print(); // note: A
	std::cout << allocator.allocate(  2, 2) << ' '; allocator.print(); // note: B
	std::cout << allocator.allocate( 10   ) << ' '; allocator.print(); // note: C
	std::cout << allocator.allocate(  4   ) << ' '; allocator.print(); // note: D

	// note: A0BB 0000 | CCCC CCCC | CC00 0000 | DDDD 0000 | ...

	std::cout << allocator.allocate(988   ) << ' '; allocator.print();
	std::cout << allocator.allocate(  1   ) << ' '; allocator.print(); // note: nullptr

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}