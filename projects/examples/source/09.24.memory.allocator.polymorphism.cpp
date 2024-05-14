#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <memory_resource>
#include <vector>

#include <boost/pool/object_pool.hpp>
#include <boost/pool/pool_alloc.hpp>

#include <benchmark/benchmark.h>

//  ================================================================================================

void test_1(benchmark::State & state)
{
	constexpr std::size_t size = 1000;

	for (auto _ : state)
	{
        std::list < int > list;

		for (std::size_t i = 0; i < size; ++i) list.push_back(42);

        benchmark::DoNotOptimize(list);
	}
}

//  ================================================================================================

void test_2(benchmark::State & state)
{
	constexpr std::size_t size = 1000;

	for (auto _ : state)
	{
        std::pmr::list < int > list;

		for (std::size_t i = 0; i < size; ++i) list.push_back(42);

        benchmark::DoNotOptimize(list);
	}
}

//  ================================================================================================

void test_3(benchmark::State & state)
{
	constexpr std::size_t size = 1000;

	for (auto _ : state)
	{
        std::pmr::monotonic_buffer_resource arena;

        std::pmr::polymorphic_allocator < int > allocator(&arena);

        std::pmr::list < int > list(allocator);

		for (std::size_t i = 0; i < size; ++i) list.push_back(42);

        benchmark::DoNotOptimize(list);
	}
}

//  ================================================================================================

void test_4(benchmark::State & state)
{
	constexpr std::size_t size = 1000;

	for (auto _ : state)
	{
        std::array < std::byte, size * 32 > buffer;

        std::pmr::monotonic_buffer_resource arena(std::data(buffer), std::size(buffer));

        std::pmr::polymorphic_allocator < int > allocator(&arena);

        std::pmr::list < int > list(allocator);

		for (std::size_t i = 0; i < size; ++i) list.push_back(42);

        benchmark::DoNotOptimize(list);
	}
}

//  ================================================================================================

#define BOOST_POOL_NO_MT

void test_5(benchmark::State & state) // support: Valgrind
{
	constexpr std::size_t size = 1000;

	for (auto _ : state)
	{
        std::list < int, boost::fast_pool_allocator < int > > list;

		for (std::size_t i = 0; i < size; ++i) list.push_back(42);

        benchmark::DoNotOptimize(list);
	}
}

//  ================================================================================================

BENCHMARK(test_1);
BENCHMARK(test_2);
BENCHMARK(test_3);
BENCHMARK(test_4);
BENCHMARK(test_5);

//  ================================================================================================

int main(int argc, char ** argv)
{
    std::array < char, 64 > buffer{};

    std::ranges::fill(buffer, '_');

    std::pmr::monotonic_buffer_resource arena(std::data(buffer), std::size(buffer));

    constexpr std::size_t n_letters = 26;

    std::pmr::vector < char > letters(&arena);

    for (std::size_t i = 0; i < n_letters; ++i)
    {
        letters.push_back(static_cast < char > ('a' + i));
    }

    for (const auto element : buffer) std::cout << element;

    std::cout << std::endl;

//  ================================================================================================

    auto resource = std::pmr::new_delete_resource();

    const auto pointer = resource->allocate(1);

    resource->deallocate(pointer, 1);

//  ================================================================================================

    boost::object_pool < int > pool(32);

    auto object_1 = pool.malloc(); pool.destroy(object_1);
    auto object_2 = pool.malloc(); pool.destroy(object_2);

    assert(pool.get_next_size() == 64);

//  ================================================================================================

    std::vector < int, boost::pool_allocator < int > > vector;

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}