#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

//  ================================================================================================

struct            Entity_v1 { std::uint8_t x = 0; std::uint32_t y = 0; std::uint16_t z = 0; };
struct            Entity_v2 { std::uint8_t x = 0; std::uint16_t z = 0; std::uint32_t y = 0; };
struct alignas(8) Entity_v3 { std::uint8_t x = 0; std::uint16_t z = 0; std::uint32_t y = 0; };

//  ================================================================================================

template < typename T > void print(const std::string & name)
{
	std::cout << "alignof(" + name + ") = " << alignof(T) << '\n';
	std::cout << " sizeof(" + name + ") = " <<  sizeof(T) << '\n';
}

//  ================================================================================================

struct             Entity_v5 { std::uint8_t x = 0; };
struct alignas(64) Entity_v6 { std::uint8_t x = 0; };

//  ================================================================================================

void test_v1(benchmark::State & state)
{
	std::vector < Entity_v5 > entities_v5(1'000);
	
    for (auto value : state)
    {
		entities_v5.front().x = 1;

		for (auto i = 1uz; i < std::size(entities_v5); ++i) 
		{
			entities_v5[i].x = entities_v5[i - 1].x + 1;
		}

		benchmark::DoNotOptimize(entities_v5);
    }
}

//  ================================================================================================

void test_v2(benchmark::State & state)
{
	std::vector < Entity_v6 > entities_v6(1'000);
	
    for (auto value : state)
    {
		entities_v6.front().x = 1;

		for (auto i = 1uz; i < std::size(entities_v6); ++i) 
		{
			entities_v6[i].x = entities_v6[i - 1].x + 1;
		}

		benchmark::DoNotOptimize(entities_v6);
    }
}

//  ================================================================================================

BENCHMARK(test_v1);
BENCHMARK(test_v2);

//  ================================================================================================

int main(int argc, char ** argv)
{
	static_assert(std::alignment_of_v < double > == 8);

//  ------------------------------------------------------------------------------------------------

	print < Entity_v1 > ("Entity_v1");
	print < Entity_v2 > ("Entity_v2");
	print < Entity_v3 > ("Entity_v3");

//  ------------------------------------------------------------------------------------------------

	alignas(16) int array_1[]{ 1, 2, 3, 4, 5 };
	alignas(64) int array_2[]{ 1, 2, 3, 4, 5 };

	std::cout << "array_1 = " << std::hex << array_1 << '\n';
	std::cout << "array_1 = " << std::hex << array_2 << '\n';

//  ------------------------------------------------------------------------------------------------

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();
}