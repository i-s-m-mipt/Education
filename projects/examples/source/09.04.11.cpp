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

template < std::size_t S > class Allocator : private boost::noncopyable
{
public :

	auto allocate(std::size_t size, std::size_t alignment = s_alignment) -> void *
	{
		void * begin = m_begin + m_offset;

		auto free = S - m_offset;

		if (begin = std::align(alignment, size, begin, free); begin)
		{
			m_offset = S - free + size;
			
			return begin;
		}
		else 
		{
			return nullptr;
		}
	}

//  ------------------------------------------------------------------------------

	void test() const
	{
		std::cout << "Allocator::test : S = " << S << ' ';

		auto begin = static_cast < void * > (m_begin);

		std::cout << "m_begin = "  << std::format("{:018}", begin) << ' ';

		std::cout << "m_offset = " << std::format("{:0>4}", m_offset) << '\n';
	}

private :

	std::size_t m_offset = 0;

    alignas(std::max_align_t) std::byte m_array[S]{};

    std::byte * m_begin = m_array;

//  ------------------------------------------------------------------------------

	static inline auto s_alignment = alignof(std::max_align_t);
};

//////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz;

	for (auto element : state)
	{
		Allocator < 1'024 * 1'024 > allocator;

		for (auto i = 0uz; i < kb; ++i)
		{
			benchmark::DoNotOptimize(allocator.allocate(kb));
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	auto kb = 1'024uz;

	std::vector < void * > vector(kb, nullptr);

	for (auto element : state)
	{
		for (auto i = 0uz; i < kb; ++i)
		{
			vector[i] = operator new(kb);
		}

		for (auto i = 0uz; i < kb; ++i)
		{
			operator delete(vector[i]);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

//////////////////////////////////////////////////////////////////////////////////

int main()
{
	Allocator < 1'024 > allocator;

//  ----------------------------------------------------------------------

	allocator.test();

//  ----------------------------------------------------------------------

	[[maybe_unused]] auto x1 = allocator.allocate(1, 1); allocator.test();

	[[maybe_unused]] auto x2 = allocator.allocate(2, 2); allocator.test();
		
	[[maybe_unused]] auto x3 = allocator.allocate(4, 4); allocator.test();

	[[maybe_unused]] auto x4 = allocator.allocate(8, 8); allocator.test();

//  ----------------------------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}

//////////////////////////////////////////////////////////////////////////////////