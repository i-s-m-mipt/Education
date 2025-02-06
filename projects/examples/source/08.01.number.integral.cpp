#include <bit>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <format>
#include <ios>
#include <iostream>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

//////////////////////////////////////////////////////////////////////////////////////////////////

struct Timestamp
{
    unsigned int second :  6 = 0;
    unsigned int minute :  6 = 0;
    unsigned int hour   :  5 = 0;
    unsigned int day    :  5 = 0;
    unsigned int month  :  4 = 0;
    unsigned int year   : 32 = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

struct Entity_v1 { std::uint32_t x : 15 = 0, y : 17 = 0; };

struct Entity_v2 { std::uint32_t x      = 0, y      = 0; };

//////////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    std::vector < Entity_v1 > entities(1'000);

    for (auto element : state)
    {
        for (auto i = 1uz; i < std::size(entities); ++i)
        {
            entities[i].x = i;

            entities[i].y = entities[i].x + entities[i - 1].y;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    std::vector < Entity_v2 > entities(1'000);

    for (auto element : state)
    {        
        for (auto i = 1uz; i < std::size(entities); ++i)
        {
            entities[i].x = i;

            entities[i].y = entities[i].x + entities[i - 1].y;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void test_v3(benchmark::State & state) // support: compiler-explorer.com
{
    for (auto element : state)
    {
        auto x = 1.0;
        
        benchmark::DoNotOptimize(*reinterpret_cast < char * > (&x));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void test_v4(benchmark::State & state) // support: compiler-explorer.com
{
    for (auto element : state)
    {
        auto x = 1.0;

        benchmark::DoNotOptimize(*std::bit_cast < char * > (&x));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

BENCHMARK(test_v3);

BENCHMARK(test_v4);

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        assert(std::format("{:#b}", 0b11111111) == "0b11111111");

        assert(std::format("{:#o}", 0377) == "0377");

        assert(std::format("{:#d}", 255) == "255");

        assert(std::format("{:#x}", 0xff) == "0xff");
    }

//  ----------------------------------------------------------------------------------------------

    {
        assert((0x1234 &  0x00ff) == 0x0034);
        assert((0x1234 & ~0x00ff) == 0x1200);
        assert((0x1234 |  0x00ff) == 0x12ff);
        assert((0x1234 ^  0x00ff) == 0x12cb);
        assert((0x3400 >> 0x0008) == 0x0034);
        assert((0x0012 << 0x0008) == 0x1200);
    }

//  ----------------------------------------------------------------------------------------------

    {
        assert(1 << 2 == 4 && 4 >> 2 == 1);
    }

//  ----------------------------------------------------------------------------------------------

    {
        auto x = 1, y = 2;
        
        x ^= y ^= x ^= y;
        
        assert(x == 2 && y == 1);
    }

//  ----------------------------------------------------------------------------------------------

    {
        static_assert(sizeof(Timestamp) == 8);

        Timestamp timestamp(0, 0, 0, 1, 1, 1970);

//      auto ptr = &timestamp.year; // error
    }

//  ----------------------------------------------------------------------------------------------

    {
        assert((std::bitset < 8 > (0b01) & std::bitset < 8 > (0b10)) == 0b00);

        assert((std::bitset < 8 > (0b01) | std::bitset < 8 > (0b10)) == 0b11);

        assert( std::bitset < 8 > (255).to_string() == "11111111");

        assert( std::bitset < 8 > ("11111111").to_ullong() == 255);

        assert( std::bit_floor(3u) == 2 && std::bit_ceil(3u) == 4);
    }

//  ----------------------------------------------------------------------------------------------

    {
        assert((std::byte(0b01) & std::byte(0b10)) == std::byte(0b00));

        assert((std::byte(0b01) | std::byte(0b10)) == std::byte(0b11));
    }

//  ----------------------------------------------------------------------------------------------

    {
        auto is_endian_little = std::endian::native == std::endian::little;

        std::cout << "main : is_endian_little = " << std::format("{}", is_endian_little) << '\n';
    }
    
//  ----------------------------------------------------------------------------------------------

    {
        auto x = 0x01020304;

        auto p_x_1 = &x;

        auto p_x_2 = std::bit_cast < std::byte * > (p_x_1);

        std::cout << "main : x = { ";

        for (auto i = 0uz; i < sizeof(unsigned int); ++i)
        {
            std::cout << std::format("{:#04x}", std::to_integer < int > (*(p_x_2 + i))) << ' ';
        }

        std::cout << "}\n";
    }

//  ----------------------------------------------------------------------------------------------

    {
        int array[5]{ 1, 2, 3, 4, 5 };

        auto ptr_1 = &array[std::size(array) - 1], ptr_2 = &array[0];

        assert
        (
            sizeof(array[0]) * (ptr_1 - ptr_2) == static_cast < std::size_t >
            (
                std::bit_cast < std::byte * > (ptr_1) - 

                std::bit_cast < std::byte * > (ptr_2)
            )
        );
    }

//  ----------------------------------------------------------------------------------------------

    {
        assert(sizeof(std::int16_t) == 2 && sizeof(std::int_least16_t) >= 2);

	    assert(sizeof(std::int32_t) == 4 && sizeof(std::int_least32_t) >= 4);

	    assert(sizeof(std::int64_t) == 8 && sizeof(std::int_least64_t) >= 8);
    }

//  ----------------------------------------------------------------------------------------------

    {
        auto x = 1.0; [[maybe_unused]] std::uint64_t y;
    
//      *reinterpret_cast < double * > (&y) = x; // bad

//      y = *reinterpret_cast < std::uint64_t * > (&x); // bad

        y = std::bit_cast < std::uint64_t > (x);
    }

//  ----------------------------------------------------------------------------------------------

    {
        benchmark::RunSpecifiedBenchmarks();
    }
}