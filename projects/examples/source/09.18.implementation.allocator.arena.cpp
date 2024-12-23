#include <cstddef>
#include <format>
#include <iomanip>
#include <iostream>
#include <memory>
#include <new>
#include <vector>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////////////

class Arena_Allocator : private boost::noncopyable
{
public:

	explicit Arena_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = operator new(m_size, std::align_val_t(default_alignment));
	}

   ~Arena_Allocator()
	{
		if (m_begin)
		{
			operator delete(m_begin, m_size, std::align_val_t(default_alignment));
		}
	}

//  ------------------------------------------------------------------------------------

	auto allocate(std::size_t size, std::size_t alignment = default_alignment) -> void * 
	{
		void * first = get_byte(m_begin) + m_offset;

		auto space = m_size - m_offset;

		if (first = std::align(alignment, size, first, space); first)
		{
			m_offset = m_size - space + size; 
			
			return first;
		}
		else 
		{
			return nullptr;
		}
	}

//  ------------------------------------------------------------------------------------

	void test() const
	{
		std::cout << "Arena_Allocator::test : ";

		std::cout << "m_size = " << m_size << ' ';

		std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';

		std::cout << "m_offset = " << std::setw(4) << std::setfill('0') << std::right;
		
		std::cout <<  m_offset << '\n';
	}

private:

	auto get_byte(void * ptr) const -> std::byte *
	{
		return static_cast < std::byte * > (ptr);
	}

//  ------------------------------------------------------------------------------------

	std::size_t m_size = 0, m_offset = 0; 
	
	void * m_begin = nullptr;

//  ------------------------------------------------------------------------------------

	static inline auto default_alignment = alignof(std::max_align_t);
};

////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

	for (auto value : state)
	{
		Arena_Allocator allocator(gb);

		for (auto i = 0uz; i < kb; ++i)
		{
			benchmark::DoNotOptimize(allocator.allocate(mb));
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////

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
			operator delete(ptrs[i], mb); 
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);
BENCHMARK(test_v2);

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Arena_Allocator allocator(1'024); 

	allocator.test();

	[[maybe_unused]] auto ptr_1 = allocator.allocate(1, 1); allocator.test();
	[[maybe_unused]] auto ptr_2 = allocator.allocate(2, 2); allocator.test();
	[[maybe_unused]] auto ptr_3 = allocator.allocate(4, 4); allocator.test();
	[[maybe_unused]] auto ptr_4 = allocator.allocate(8, 8); allocator.test();

//  -------------------------------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}