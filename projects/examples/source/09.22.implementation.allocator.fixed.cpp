#include <cstddef>
#include <format>
#include <iostream>
#include <memory>
#include <new>
#include <vector>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

template < std::size_t S > class Fixed_Allocator : private boost::noncopyable
{
public:

	auto allocate(std::size_t size, std::size_t alignment = default_alignment) -> void *
	{
		void * begin = m_begin + m_offset;

		auto space = S - m_offset;

		if (begin = std::align(alignment, size, begin, space); begin)
		{
			m_offset = S - space + size; 
			
			return begin;
		}
		else 
		{
			return nullptr;
		}
	}

//  ------------------------------------------------------------------------------------------------

	void test() const
	{
		std::cout << "Fixed_Allocator::test : S = " << S << ' ';

		auto begin = static_cast < void * > (m_begin);

		std::cout << "m_begin = "  << std::format("{:018}", begin) << ' ';

		std::cout << "m_offset = " << std::format("{:0>4}", m_offset) << '\n';
	}

private:

	std::size_t m_offset = 0;

    alignas(std::max_align_t) std::byte m_buffer[S]{};

    std::byte * m_begin = m_buffer;

//  ------------------------------------------------------------------------------------------------

	static inline auto default_alignment = alignof(std::max_align_t);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz;

	for (auto element : state)
	{
		Fixed_Allocator < 1'024 * 1'024 > allocator;

		for (auto i = 0uz; i < kb; ++i)
		{
			benchmark::DoNotOptimize(allocator.allocate(kb));
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	auto kb = 1'024uz;

	std::vector < void * > ptrs(kb, nullptr);

	for (auto element : state)
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

////////////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);
BENCHMARK(test_v2);

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Fixed_Allocator < 1'024 > allocator; 

	allocator.test();

	[[maybe_unused]] auto ptr_1 = allocator.allocate(1, 1); allocator.test();

	[[maybe_unused]] auto ptr_2 = allocator.allocate(2, 2); allocator.test();
	
	[[maybe_unused]] auto ptr_3 = allocator.allocate(4, 4); allocator.test();

	[[maybe_unused]] auto ptr_4 = allocator.allocate(8, 8); allocator.test();

//  -------------------------------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}