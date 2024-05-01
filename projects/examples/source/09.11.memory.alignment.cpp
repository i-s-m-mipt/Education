#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <type_traits>

#include <benchmark/benchmark.h>

// =================================================================================================

struct S1 // note: C___IIIISS__
{
	char  c{}; // note: 1 byte(s)
	int   i{}; // note: 4 byte(s)
	short s{}; // note: 2 byte(s)

}; // struct S1

// =================================================================================================

struct S2 // note: C_SSIIII
{
	char  c{}; // note: 1 byte(s)
	short s{}; // note: 2 byte(s)
	int   i{}; // note: 4 byte(s)

}; // struct S2

// =================================================================================================

struct alignas(double) S3
{
	char  c{}; // note: 1 byte(s)
	short s{}; // note: 2 byte(s)
	int   i{}; // note: 4 byte(s)
	
}; // struct alignas(double) S3

// =================================================================================================

struct alignas(32) S4 { double data[4]{}; };

// =================================================================================================

struct alignas( 1) S5 { std::uint8_t x{}; };
struct alignas(64) S6 { std::uint8_t x{}; };

// =================================================================================================

void test_1(benchmark::State & state) // note: fast
{
	constexpr std::size_t size = 64;

    for (auto _ : state)
    {
        auto array = new S5[size]{}; 

		for (std::size_t i = 1; i < size; ++i) array[i].x = array[i - 1].x + 1;

		benchmark::DoNotOptimize(array);
    }
}

// =================================================================================================

void test_2(benchmark::State & state) // note: slow
{
	constexpr std::size_t size = 64;

    for (auto _ : state)
    {
        auto array = new S6[size]{}; 

		for (std::size_t i = 1; i < size; ++i) array[i].x = array[i - 1].x + 1;

		benchmark::DoNotOptimize(array);
    }
}

// =================================================================================================

BENCHMARK(test_1);
BENCHMARK(test_2);

// =================================================================================================

int main(int argc, char ** argv) // note: arguments for benchmark
{
	std::cout << "char: " << alignof(char) << ' ' << sizeof(char) << std::endl;
	std::cout << "int*: " << alignof(int*) << ' ' << sizeof(int*) << std::endl;

	std::cout << "S1: " << alignof(S1) << ' ' << sizeof(S1) << std::endl;
	std::cout << "S2: " << alignof(S2) << ' ' << sizeof(S2) << std::endl;
	std::cout << "S3: " << alignof(S3) << ' ' << sizeof(S3) << std::endl;
	std::cout << "S4: " << alignof(S4) << ' ' << sizeof(S4) << std::endl;

	static_assert(std::alignment_of_v < double > == 8);

	constexpr std::size_t size = 5;

	alignas(16) constexpr int array_1[size]{};
	alignas(64) constexpr int array_2[size]{};

	std::cout << std::hex << array_1 << std::endl;
	std::cout << std::hex << array_2 << std::endl;

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}