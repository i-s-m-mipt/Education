#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <list>
#include <memory_resource>
#include <string>
#include <vector>

using namespace std::literals;

#include <boost/pool/object_pool.hpp>
#include <boost/pool/pool_alloc.hpp>

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	for (auto element : state)
	{
        std::list < int > list;

		for (auto i = 0uz; i < 1'000; ++i) 
        {
            list.push_back(1);
        }

        benchmark::DoNotOptimize(list);
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	for (auto element : state)
	{
        std::pmr::list < int > list;

		for (auto i = 0uz; i < 1'000; ++i) 
        {
            list.push_back(1);
        }

        benchmark::DoNotOptimize(list);
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void test_v3(benchmark::State & state)
{
	for (auto element : state)
	{
        std::pmr::monotonic_buffer_resource arena;

        std::pmr::polymorphic_allocator < int > allocator(&arena);

        std::pmr::list < int > list(allocator);

		for (auto i = 0uz; i < 1'000; ++i) 
        {
            list.push_back(1);
        }

        benchmark::DoNotOptimize(list);
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void test_v4(benchmark::State & state)
{
	for (auto element : state)
	{
        std::array < std::byte, 32'000 > array;

        std::pmr::monotonic_buffer_resource arena(std::data(array), std::size(array));

        std::pmr::polymorphic_allocator < int > allocator(&arena);

        std::pmr::list < int > list(allocator);

		for (auto i = 0uz; i < 1'000; ++i) 
        {
            list.push_back(1);
        }

        benchmark::DoNotOptimize(list);
	}
}

////////////////////////////////////////////////////////////////////////////////////////

#define BOOST_POOL_NO_MT

void test_v5(benchmark::State & state) // support: Valgrind
{
	for (auto element : state)
	{
        std::list < int, boost::fast_pool_allocator < int > > list;

		for (auto i = 0uz; i < 1'000; ++i) 
        {
            list.push_back(1);
        }

        benchmark::DoNotOptimize(list);
	}
}

////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

BENCHMARK(test_v3);

BENCHMARK(test_v4);

BENCHMARK(test_v5);

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        std::array < char, 32 > array;

        std::ranges::fill(array, '_');

        std::pmr::monotonic_buffer_resource arena(std::data(array), std::size(array));

        auto size = 26uz;

        std::pmr::vector < char > vector(&arena);

        vector.reserve(size);

        for (auto i = 0uz; i < size; ++i)
        {
            vector.push_back('a' + i);
        }

        auto result = "abcdefghijklmnopqrstuvwxyz______"s;

        for (auto i = 0uz; i < std::size(array); ++i) 
        {
            assert(array[i] == result[i]);
        }
    }

//  ------------------------------------------------------------------------------------

    {
        auto resource = std::pmr::new_delete_resource();

        auto ptr = resource->allocate(1);

        resource->deallocate(ptr, 1);
    }

//  ------------------------------------------------------------------------------------

    {
        boost::object_pool < int > pool(32);

        auto object_1 = pool.malloc(); pool.destroy(object_1);

        auto object_2 = pool.malloc(); pool.destroy(object_2);

        assert(pool.get_next_size() == 64);
    }

//  ------------------------------------------------------------------------------------

    {
        std::vector < int, boost::pool_allocator < int > > vector;
    }

//  ------------------------------------------------------------------------------------

	{
        benchmark::RunSpecifiedBenchmarks();
    }
}