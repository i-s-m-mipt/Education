#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

//  ================================================================================================

class Stack_Allocator : private boost::noncopyable
{
private:

	using Header = std::uint8_t;

public:

	explicit Stack_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size, std::align_val_t(default_alignment));
	}

   ~Stack_Allocator()
	{
		if (m_begin)
		{
			::operator delete(m_begin, m_size, std::align_val_t(default_alignment));
		}
	}

public:

	void * allocate(std::size_t size, std::size_t alignment = default_alignment) 
	{
		void * first = get_byte(m_begin) + m_offset;

		void * block = get_byte(first) + sizeof(Header);

		auto space = m_size - m_offset - sizeof(Header);

		if (block = std::align(alignment, size, block, space); block)
		{
			auto header = get_header(get_byte(block) - sizeof(Header));

			*header = static_cast < Header > (std::distance(get_byte(first), get_byte(block)));

			m_offset = get_byte(block) - get_byte(m_begin) + size;

			return block;
		}
		else 
		{
			return nullptr;
		}
	}

	void deallocate(void * ptr)
	{
		auto header = get_header(get_byte(ptr) - sizeof(Header));

		m_offset = get_byte(ptr) - get_byte(m_begin) - *header;
	}

	void print() const
	{
		std::cout << m_begin << " : ";

		std::cout << std::setw(4) << std::setfill('0') << std::right << m_offset;

		std::cout << " / " << m_size << std::endl;
	}

private:

	std::byte * get_byte(void * ptr) const
	{
		return static_cast < std::byte * > (ptr);
	}

	Header * get_header(void * ptr) const
	{
		return static_cast < Header * > (ptr);
	}

private:

	static inline const auto default_alignment = alignof(std::max_align_t);

//  -----------------------------------------------------------------------

	std::size_t m_size   = 0;
	std::size_t m_offset = 0;

	void * m_begin = nullptr;
};

//  ================================================================================================

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

	std::vector < void * > ptrs(kb, nullptr);

	for (auto value : state)
	{
		Stack_Allocator allocator(2 * gb);

		for (auto i = 0uz; i < kb; ++i)
		{
			ptrs[i] = allocator.allocate(mb);
		}

		for (auto i = 0uz; i < kb; ++i)
		{
			allocator.deallocate(ptrs[std::size(ptrs) - 1 - i]);
		}
	}
}

//  ================================================================================================

void test_v2(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb;

	std::vector < void * > ptrs(kb, nullptr);

	for (auto value : state)
	{
		for (auto i = 0uz; i < kb; ++i)
		{
			ptrs[i] = ::operator new(mb);
		}

		for (auto i = 0uz; i < kb; ++i)
		{
			::operator delete(ptrs[std::size(ptrs) - 1 - i], mb);
		}
	}
}

//  ================================================================================================

BENCHMARK(test_v1);
BENCHMARK(test_v2);

//  ================================================================================================

int main(int argc, char ** argv)
{
	Stack_Allocator allocator(1024);

	allocator.print();

	[[maybe_unused]] auto ptr_1 = allocator.allocate( 1, 4); allocator.print();
	[[maybe_unused]] auto ptr_2 = allocator.allocate( 2, 2); allocator.print();
	[[maybe_unused]] auto ptr_3 = allocator.allocate(10   ); allocator.print();
	[[maybe_unused]] auto ptr_4 = allocator.allocate( 4   ); allocator.print();

	allocator.deallocate(ptr_4); allocator.print();
	allocator.deallocate(ptr_3); allocator.print();

	[[maybe_unused]] auto ptr_5 = allocator.allocate( 3, 4); allocator.print();
	[[maybe_unused]] auto ptr_6 = allocator.allocate( 8   ); allocator.print(); 

	// detail: 000H 1H22 | 000H 555H | 6666 6666 | ...

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();
}