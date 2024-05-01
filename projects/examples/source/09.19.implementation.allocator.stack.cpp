#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

// =================================================================================================

class Stack_Allocator : private boost::noncopyable // note: deallocations at end for blocks of different sizes
{
private:

	using Header = std::uint8_t;

public:

	explicit Stack_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size, default_alignment);
	}

   ~Stack_Allocator() noexcept
	{
		::operator delete(m_begin, m_size, default_alignment);
	}

public:

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) noexcept
	{
		void * const first = get_byte(m_begin) + m_offset;

		void *       block = get_byte(first) + sizeof(Header); // note: first byte for data after header

		auto space = m_size - m_offset - sizeof(Header);

		if (block = std::align(alignment, size, block, space); block) // note: modifies block and space
		{
			const auto header = get_header(get_byte(block) - sizeof(Header));

			*header = static_cast < Header > (std::distance(get_byte(first), get_byte(block)));

			m_offset = get_byte(block) - get_byte(m_begin) + size;

			return block; // note: aligned pointer
		}
		else return nullptr;
	}

	void deallocate(void * ptr) noexcept
	{
		const auto header = get_header(get_byte(ptr) - sizeof(Header));

		m_offset = get_byte(ptr) - get_byte(m_begin) - *header;
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

	[[nodiscard]] Header * get_header(void * ptr) const noexcept
	{
		return static_cast < Header * > (ptr);
	}

public:

	static constexpr std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

	const std::size_t m_size;

private:

	std::size_t m_offset = 0;

	void * m_begin = nullptr;

}; // class Stack_Allocator : private boost::noncopyable

// =================================================================================================

void test_1(benchmark::State & state) // note: fast
{
	constexpr std::size_t kb = 1024, mb = kb * kb, gb = kb * kb * kb;

	std::vector < void * > pointers(kb, nullptr);

	for (auto _ : state)
	{
		Stack_Allocator allocator(2 * gb); // note: huge constant

		for (std::size_t i = 0; i < kb; ++i)
		{
			pointers[i] = allocator.allocate(mb);
		}

		for (std::size_t i = 0; i < kb; ++i)
		{
			allocator.deallocate(pointers[std::size(pointers) - 1 - i]);
		}
	}
}

// =================================================================================================

void test_2(benchmark::State & state) // note: slow
{
	constexpr std::size_t kb = 1024, mb = kb * kb;

	std::vector < void * > pointers(kb, nullptr);

	for (auto _ : state)
	{
		for (std::size_t i = 0; i < kb; ++i)
		{
			pointers[i] = ::operator new(mb);
		}

		for (std::size_t i = 0; i < kb; ++i)
		{
			::operator delete(pointers[std::size(pointers) - 1 - i], mb);
		}
	}
}

// =================================================================================================

BENCHMARK(test_1);
BENCHMARK(test_2);

// =================================================================================================

int main(int argc, char ** argv) // note: arguments for benchmark
{
	Stack_Allocator allocator(1024);

	auto ptr_A = allocator.allocate( 1, 4); std::cout << ptr_A << ' '; allocator.print();
	auto ptr_B = allocator.allocate( 2, 2); std::cout << ptr_B << ' '; allocator.print();
	auto ptr_C = allocator.allocate(10   ); std::cout << ptr_C << ' '; allocator.print();
	auto ptr_D = allocator.allocate( 4   ); std::cout << ptr_D << ' '; allocator.print();

	// note: 000H AHBB | 0000 000H | CCCC CCCC | CC00 000H | DDDD 0000 | ...

	allocator.deallocate(ptr_D);    std::cout << std::string(17, ' '); allocator.print();
	allocator.deallocate(ptr_C);    std::cout << std::string(17, ' '); allocator.print();

	// note: 000H AHBB | ...

	auto ptr_E = allocator.allocate( 3, 4); std::cout << ptr_E << ' '; allocator.print();
	auto ptr_F = allocator.allocate( 8   ); std::cout << ptr_F << ' '; allocator.print(); 

	// note: 000H AHBB | 000H EEEH | FFFF FFFF | ...

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}