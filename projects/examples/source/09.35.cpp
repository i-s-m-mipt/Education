///////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

///////////////////////////////////////////////////////////////////////////////////////////////////

// content : Microbenchmarking
//
// content : Containers std::list and std::pmr::list

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <list>
#include <memory_resource>

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    for (auto element : state)
    {
        std::list < int > list;

        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            list.push_back(1);
        }

        benchmark::DoNotOptimize(list);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    for (auto element : state)
    {
        std::pmr::list < int > list;

        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            list.push_back(1);
        }

        benchmark::DoNotOptimize(list);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void test_v3(benchmark::State & state)
{
    for (auto element : state)
    {
        std::pmr::monotonic_buffer_resource resource;

        std::pmr::polymorphic_allocator < int > allocator(&resource);

        std::pmr::list < int > list(allocator);

        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            list.push_back(1);
        }

        benchmark::DoNotOptimize(list);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void test_v4(benchmark::State & state)
{
    for (auto element : state)
    {
        auto size = 32uz << 10, alignment = alignof(std::max_align_t);

        auto array = static_cast < std::byte * > (operator new(size, std::align_val_t(alignment)));

        std::pmr::monotonic_buffer_resource resource(array, size, std::pmr::new_delete_resource());

        std::pmr::polymorphic_allocator < int > allocator(&resource);

        std::pmr::list < int > list(allocator);

        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            list.push_back(1);
        }

        operator delete(array, size, std::align_val_t(alignment));

        benchmark::DoNotOptimize(list);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

BENCHMARK(test_v3);

BENCHMARK(test_v4);

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////////////////////