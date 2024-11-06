#include <bit>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <span>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

//  ================================================================================================

void print(std::span < const std::byte > bytes)
{
    std::cout << std::boolalpha << (std::endian::native == std::endian::little) << std::endl;

    for (auto i = 0uz; i < sizeof(int); ++i)
    {
        if (auto byte = std::to_integer < int > (bytes[i]); byte != 0)
        {
            std::cout << std::hex << byte << ' ';
        }
    }
        
    std::cout << std::endl;
}

//  ================================================================================================

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

//  ================================================================================================

void test_v1(benchmark::State & state) // support: compiler-explorer.com
{
    for (auto value : state)
    {
        auto x = 1.0; 
        
        benchmark::DoNotOptimize(*reinterpret_cast < char * > (&x));
    }
}

//  ================================================================================================

void test_v2(benchmark::State & state) // support: compiler-explorer.com
{
    for (auto value : state)
    {
        auto x = 1.0;

        benchmark::DoNotOptimize(*std::bit_cast < char * > (&x));
    }
}

//  ================================================================================================

struct Entity_v1 { std::uint32_t x : 15 = 0, y : 17 = 0; };
struct Entity_v2 { std::uint32_t x      = 0, y      = 0; };

//  ================================================================================================

void test_v3(benchmark::State & state)
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

//  ================================================================================================

void test_v4(benchmark::State & state)
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

//  ================================================================================================

BENCHMARK(test_v1);
BENCHMARK(test_v2);
BENCHMARK(test_v3);
BENCHMARK(test_v4);

//  ================================================================================================

int main(int argc, char ** argv)
{
    std::cout << std::showbase;

    std::cout << std::oct << 42 << std::endl;
    std::cout << std::dec << 42 << std::endl;
    std::cout << std::hex << 42 << std::endl;

    [[maybe_unused]] auto bin = 0b101010;
    [[maybe_unused]] auto oct = 052;
    [[maybe_unused]] auto dec = 42;
    [[maybe_unused]] auto hex = 0x2a;

//  ================================================================================================

    static_assert((0x1234 &  0x00ff) == 0x0034);
    static_assert((0x1234 & ~0x00ff) == 0x1200);
    static_assert((0x1234 |  0x00ff) == 0x12ff);
    static_assert((0x1234 ^  0x00ff) == 0x12cb);
    static_assert((0x3400 >> 0x0008) == 0x0034);
    static_assert((0x0012 << 0x0008) == 0x1200);

//  ================================================================================================

    static_assert(1 << 2 == 4);
    static_assert(4 >> 2 == 1);

//  ================================================================================================

    auto x = 1, y = 2; x ^= y ^= x ^= y; assert(x == 2 && y == 1);

//  ================================================================================================

    static_assert(sizeof(std::uint16_t) == 2);
	static_assert(sizeof(std::uint32_t) == 4);
	static_assert(sizeof(std::uint64_t) == 8);

    static_assert(std::is_same_v < int, std::int32_t > );

//  ================================================================================================

    std::bitset < 8 > bitset(0b1101); // support: boost::dynamic_bitset
        
    bitset |= 0b0010; assert(bitset == 0b1111);
    bitset &= 0b0011; assert(bitset == 0b0011);

    std::cout << std::bitset < 8 > (42) << std::endl; // output: 00101010
   
    assert(std::bitset < 8 > (       42 ).to_string() == "00101010");
    assert(std::bitset < 8 > ("00101010").to_ullong() ==        42 );

//  ================================================================================================

    auto byte_1 = static_cast < std::byte > (1);

    auto byte_2 = static_cast < std::byte > (0b0000'1111);

    assert(std::to_integer < int > (byte_1 & byte_2) == 0b0000'0001);
    assert(std::to_integer < int > (byte_1 | byte_2) == 0b0000'1111);
    
//  ================================================================================================

    int array[]{ 1, 2, 3, 4, 5 };

    print(std::as_bytes(std::span < int > (array)));

//  ================================================================================================

    auto   value = std::numeric_limits < unsigned int > ::max();

    auto p_value = &value;

    auto p_value_byte = std::bit_cast < std::byte * > (p_value);

    for (auto i = 0uz; i < sizeof(unsigned int); ++i)
    {
        assert(std::to_integer < int > (*(p_value_byte + i)) == 0xff);
    }

    auto ptr_1 = &array[std::size(array) - 1], ptr_2 = &array[0];

    assert
    (
        (ptr_1 - ptr_2) * sizeof(array[0]) == static_cast < std::size_t >
        (
            std::bit_cast < std::byte * > (ptr_1) - 
            std::bit_cast < std::byte * > (ptr_2)
        )
    );

//  ================================================================================================

    auto d = 1.0; std::uint64_t result;

    static_assert(sizeof(d) == sizeof(result));

//  result = *reinterpret_cast < std::uint64_t * > (&d); // bad

    result = std::bit_cast < std::uint64_t > (d); // support: std::memcpy

//  ================================================================================================

    using binary = std::bitset < 8 > ;

    for (unsigned int i = 0; i < 10; ++i)
    {
        std::cout <<  "ceil(" << binary(i) << ") = " << binary(std::bit_ceil (i)) << ", ";
        std::cout << "floor(" << binary(i) << ") = " << binary(std::bit_floor(i)) << std::endl;
    }

//  ================================================================================================

    benchmark::Initialize(&argc, argv);

    benchmark::RunSpecifiedBenchmarks();
}