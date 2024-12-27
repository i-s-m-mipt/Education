#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>
#include <iterator>
#include <memory>
#include <new>
#include <vector>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////////

class Stack_Allocator : private boost::noncopyable
{
public:

	Stack_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = operator new(m_size, std::align_val_t(default_alignment));
	}

   ~Stack_Allocator()
	{
		if (m_begin)
		{
			operator delete(m_begin, m_size, std::align_val_t(default_alignment));
		}
	}

//  -------------------------------------------------------------------------------------------

	auto allocate(std::size_t size, std::size_t alignment = default_alignment) -> void *
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

//  -------------------------------------------------------------------------------------------

	void test() const
	{
		std::cout << "Stack_Allocator::test : m_size = " << m_size    << ' ';

		std::cout << "m_begin = "  << std::format("{:018}", m_begin ) << ' ';

		std::cout << "m_offset = " << std::format("{:0>4}", m_offset) << '\n';
	}

private:

	using Header = std::uint8_t;

//  -------------------------------------------------------------------------------------------

	auto get_byte(void * ptr) const -> std::byte *
	{
		return static_cast < std::byte * > (ptr);
	}

	auto get_header(void * ptr) const -> Header *
	{
		return static_cast < Header * > (ptr);
	}

//  -------------------------------------------------------------------------------------------

	std::size_t m_size = 0, m_offset = 0; 
	
	void * m_begin = nullptr;

//  -------------------------------------------------------------------------------------------

	static inline auto default_alignment = alignof(std::max_align_t);
};

///////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////

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

		for (auto i = 0uz; i < kb; ++i)
		{
			operator delete(ptrs[std::size(ptrs) - 1 - i], mb);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);
BENCHMARK(test_v2);

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Stack_Allocator allocator(1'024);

	allocator.test();

	[[maybe_unused]] auto ptr_1 = allocator.allocate(1, 1); allocator.test();
	[[maybe_unused]] auto ptr_2 = allocator.allocate(2, 2); allocator.test();
	[[maybe_unused]] auto ptr_3 = allocator.allocate(4, 4); allocator.test();
	[[maybe_unused]] auto ptr_4 = allocator.allocate(8, 8); allocator.test();

	allocator.deallocate (ptr_4); 							allocator.test();

	[[maybe_unused]] auto ptr_5 = allocator.allocate(8, 8); allocator.test(); 

//  --------------------------------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}