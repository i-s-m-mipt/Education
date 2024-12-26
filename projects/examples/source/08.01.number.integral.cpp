#include <bit>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <iostream>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////////////////////////////////

struct Datetime
{
    unsigned int milli  : 10 = 0;
    unsigned int second :  6 = 0;
    unsigned int minute :  6 = 0;
    unsigned int hour   :  5 = 0;
    unsigned int day    :  5 = 0;
    unsigned int month  :  4 = 0;
    unsigned int year   : 28 = 0;
};

//////////////////////////////////////////////////////////////////////////////////////

struct Entity_v1 { std::uint32_t x : 15 = 0, y : 17 = 0; };
struct Entity_v2 { std::uint32_t x      = 0, y      = 0; };

//////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    static_assert(sizeof(Entity_v1) == 4);

    std::vector < Entity_v1 > entities(1'000);

    for (auto value : state)
    {
        entities[0].x = entities[0].y = 0;

        for (auto i = 1uz; i < std::size(entities); ++i)
        {
            entities[i].x = static_cast < std::uint32_t > (i);

            entities[i].y = entities[i].x + entities[i - 1].y;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    static_assert(sizeof(Entity_v2) == 8);

    std::vector < Entity_v2 > entities(1'000);

    for (auto value : state)
    {
        entities[0].x = entities[0].y = 0;
        
        for (auto i = 1uz; i < std::size(entities); ++i)
        {
            entities[i].x = static_cast < std::uint32_t > (i);

            entities[i].y = entities[i].x + entities[i - 1].y;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void test_v3(benchmark::State & state) // support: compiler-explorer.com
{
    for (auto value : state)
    {
        auto d = 1.0; 
        
        benchmark::DoNotOptimize(*reinterpret_cast < char * > (&d));
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void test_v4(benchmark::State & state) // support: compiler-explorer.com
{
    for (auto value : state)
    {
        auto d = 1.0;

        benchmark::DoNotOptimize(*std::bit_cast < char * > (&d));
    }
}

//////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);
BENCHMARK(test_v2);
BENCHMARK(test_v3);
BENCHMARK(test_v4);

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << std::showbase;

    std::cout << "main : 255 (oct) = " << std::oct << 255 << '\n';
    std::cout << "main : 255 (dec) = " << std::dec << 255 << '\n';
    std::cout << "main : 255 (hex) = " << std::hex << 255 << '\n';

//  ----------------------------------------------------------------------------------

    [[maybe_unused]] auto x_bin = 0b11111111;
    [[maybe_unused]] auto x_oct = 0377;
    [[maybe_unused]] auto x_dec = 255;
    [[maybe_unused]] auto x_hex = 0xff;

//  ----------------------------------------------------------------------------------

    static_assert((0x1234 &  0x00ff) == 0x0034);
    static_assert((0x1234 & ~0x00ff) == 0x1200);
    static_assert((0x1234 |  0x00ff) == 0x12ff);
    static_assert((0x1234 ^  0x00ff) == 0x12cb);
    static_assert((0x3400 >> 0x0008) == 0x0034);
    static_assert((0x0012 << 0x0008) == 0x1200);

//  ----------------------------------------------------------------------------------

    static_assert(1 << 2 == 4);
    static_assert(4 >> 2 == 1);

//  ----------------------------------------------------------------------------------

    auto x = 1, y = 2; x ^= y ^= x ^= y; assert(x == 2 && y == 1);

//  ----------------------------------------------------------------------------------

    std::bitset < 8 > bitset(0b11111111); // support: boost::dynamic_bitset
        
    static_assert((std::bitset < 8 > (0b01) & std::bitset < 8 > (0b10)) == 0b00);
    static_assert((std::bitset < 8 > (0b01) | std::bitset < 8 > (0b10)) == 0b11);

    static_assert( std::bitset < 8 > (      255 ).to_string() == "11111111");
    static_assert( std::bitset < 8 > ("11111111").to_ullong() ==       255 );

    std::cout << "main : 255 (bin) = " << std::bitset < 8 > (255) << '\n';

//  ----------------------------------------------------------------------------------

    static_assert(std::bit_floor(3u) == 2 && std::bit_ceil(3u) == 4);

//  ----------------------------------------------------------------------------------

    static_assert((std::byte { 0b01 } & std::byte { 0b10 }) == std::byte { 0b00 });
    static_assert((std::byte { 0b01 } | std::byte { 0b10 }) == std::byte { 0b11 });

//  ----------------------------------------------------------------------------------

    std::cout << "main : std::endian::native = std::endian::";

    std::cout << (std::endian::native == std::endian::little ? "little" : "big") << '\n';
    
//  ----------------------------------------------------------------------------------

    auto   value = 0x01020304;

    auto p_value = &value;

    auto p_value_byte = std::bit_cast < std::byte * > (p_value);

    std::cout << "main : 0x01020304 = { ";

    for (auto i = 0uz; i < sizeof(unsigned int); ++i)
    {
        std::cout << std::hex << std::to_integer < int > (*(p_value_byte + i)) << ' ';
    }

    std::cout << "}\n";

//  ----------------------------------------------------------------------------------

    int array[]{ 1, 2, 3, 4, 5 };

    auto ptr_1 = &array[std::size(array) - 1], ptr_2 = &array[0];

    assert
    (
        sizeof(array[0]) * (ptr_1 - ptr_2) == static_cast < std::size_t >
        (
            std::bit_cast < std::byte * > (ptr_1) - 
            std::bit_cast < std::byte * > (ptr_2)
        )
    );

//  ----------------------------------------------------------------------------------

    static_assert(sizeof(std::uint16_t) == 2);
	static_assert(sizeof(std::uint32_t) == 4);
	static_assert(sizeof(std::uint64_t) == 8);

    static_assert(std::is_same_v < int, std::int32_t > );

//  ----------------------------------------------------------------------------------

    auto d = 1.0; [[maybe_unused]] std::uint64_t result = 0;
    
//  *reinterpret_cast < double * > (&result) = d; // bad

//  result = *reinterpret_cast < std::uint64_t * > (&d); // bad

    result = std::bit_cast < std::uint64_t > (d);

//  ----------------------------------------------------------------------------------

    benchmark::RunSpecifiedBenchmarks();
}