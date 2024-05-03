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

void test_1(benchmark::State & state) // note: slow
{
	constexpr std::size_t size = 1'000;

	for (auto _ : state)
	{
        std::list < int > list;

		for (std::size_t i = 0; i < size; ++i) list.push_back(42);

        benchmark::DoNotOptimize(list);
	}
}

//  ================================================================================================

void test_2(benchmark::State & state) // note: slow
{
	constexpr std::size_t size = 1'000;

	for (auto _ : state)
	{
        std::pmr::list < int > list;

		for (std::size_t i = 0; i < size; ++i) list.push_back(42);

        benchmark::DoNotOptimize(list);
	}
}

//  ================================================================================================

void test_3(benchmark::State & state) // note: fast
{
	constexpr std::size_t size = 1'000;

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

void test_4(benchmark::State & state) // note: fast
{
	constexpr std::size_t size = 1'000;

	for (auto _ : state)
	{
        std::array < std::byte, size * 32 > buffer; // note: enough to fit in all nodes

        std::pmr::monotonic_buffer_resource arena(std::data(buffer), std::size(buffer));

        std::pmr::polymorphic_allocator < int > allocator(&arena);

        std::pmr::list < int > list(allocator);

		for (std::size_t i = 0; i < size; ++i) list.push_back(42);

        benchmark::DoNotOptimize(list);
	}
}

//  ================================================================================================

#define BOOST_POOL_NO_MT // note: multithreading support for Boost.Pool is disabled

void test_5(benchmark::State & state) // note: not so fast, verify with valgrind
{
	constexpr std::size_t size = 1'000;

	for (auto _ : state)
	{
        std::list < int, boost::fast_pool_allocator < int > > list; // good: separate segments 

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

int main(int argc, char ** argv) // note: arguments for benchmark
{
    std::array < char, 64 > buffer{}; // note: external stack buffer for arena

    std::ranges::fill(buffer, '_'); // note: fill elements in range

    std::pmr::monotonic_buffer_resource arena(std::data(buffer), std::size(buffer));

    constexpr std::size_t n_letters = 26;

    std::pmr::vector < char > letters(&arena); // note: type alias

    for (std::size_t i = 0; i < n_letters; ++i)
    {
        letters.push_back(static_cast < char > ('a' + i));
    }

    for (const auto element : buffer) std::cout << element; // note: output repeated data in buffer

    std::cout << std::endl;

//  ================================================================================================

    auto resource = std::pmr::new_delete_resource();

    const auto pointer = resource->allocate(1); // note: same as ::operator new

    resource->deallocate(pointer, 1); // note: same as ::operator delete

//  ================================================================================================

    boost::object_pool < int > pool(32); // note: memory managed by pool consists of segments

    auto object_1 = pool.malloc(); // note: allocates a memory block with space for 32 int values

    pool.destroy(object_1);

    auto object_2 = pool.construct(42); // note: allocates the same memory block as for ptr_1

    pool.destroy(object_2);

    assert(pool.get_next_size() == 64); // note: allocation approach similar to std::vector

//  ================================================================================================

    std::vector < int, boost::pool_allocator < int > > vector; // good: continious segments

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}