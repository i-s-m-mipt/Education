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

[[nodiscard]] inline constexpr std::uint16_t middle(std::uint32_t x) noexcept
{
    return (x >> 8) & 0xffff;
}

//  ================================================================================================

void print(const std::span < const std::byte > & bytes)
{
    std::cout << std::boolalpha << (std::endian::native == std::endian::little) << std::endl;

    for (std::size_t i = 0; i < sizeof(int); ++i)
    {
        if (auto byte = std::to_integer < int > (bytes[i]); byte != 0)
        {
            std::cout << std::hex << byte << ' ';
        }
    }
        
    std::cout << std::endl;
}

//  ================================================================================================

template < typename T1, typename T2 > 

[[nodiscard]] inline constexpr std::ptrdiff_t distance_in_bytes(const T1 * ptr_1, 
                                                                const T2 * ptr_2) noexcept
{
    return (std::bit_cast < const std::byte * > (ptr_1) - 
            std::bit_cast < const std::byte * > (ptr_2));
}

//  ================================================================================================

struct Datetime
{
    unsigned int milli  : 10 {};
    unsigned int second : 6  {};
    unsigned int minute : 6  {};
    unsigned int hour   : 5  {};
    unsigned int day    : 5  {};
    unsigned int month  : 4  {};
    unsigned int year   : 28 {};

}; // struct Datetime

//  ================================================================================================

void test_1(benchmark::State & state) // support: compiler-explorer.com
{
    for (auto _ : state)
    {
        auto d = 3.14; 
        
        benchmark::DoNotOptimize(*reinterpret_cast < char * > (&d));
    }
}

//  ================================================================================================

void test_2(benchmark::State & state) // support: compiler-explorer.com
{
    for (auto _ : state)
    {
        auto d = 3.14;

        benchmark::DoNotOptimize(*std::bit_cast < char * > (&d));
    }
}

//  ================================================================================================

struct S1 { std::uint32_t x : 15 {}, y : 17 {}; };
struct S2 { std::uint32_t x      {}, y      {}; };

//  ================================================================================================

void test_3(benchmark::State & state)
{
    static_assert(sizeof(S1) == 4);

    std::vector < S1 > vector(100);

    for (auto _ : state)
    {
        vector[0].x = vector[0].y = 0;

        for (std::size_t i = 1; i < std::size(vector); ++i)
        {
            vector[i].x = static_cast < std::uint32_t > (i);

            vector[i].y = vector[i].x + vector[i - 1].y;
        }
    }
}

//  ================================================================================================

void test_4(benchmark::State & state)
{
    static_assert(sizeof(S2) == 8);

    std::vector < S2 > vector(100);

    for (auto _ : state)
    {
        vector[0].x = vector[0].y = 0;
        
        for (std::size_t i = 1; i < std::size(vector); ++i)
        {
            vector[i].x = static_cast < std::uint32_t > (i);

            vector[i].y = vector[i].x + vector[i - 1].y;
        }
    }
}

//  ================================================================================================

BENCHMARK(test_1);
BENCHMARK(test_2);
BENCHMARK(test_3);
BENCHMARK(test_4);

//  ================================================================================================

int main(int argc, char ** argv)
{
    std::cout << std::showbase;

    std::cout << std::oct << 42 << std::endl; // output: 052
    std::cout << std::dec << 42 << std::endl; // output: 42
    std::cout << std::hex << 42 << std::endl; // output: 0x2a

    [[maybe_unused]] constexpr auto bin = 0b101010;
    [[maybe_unused]] constexpr auto oct = 052;
    [[maybe_unused]] constexpr auto dec = 42;
    [[maybe_unused]] constexpr auto hex = 0x2a;

//  ================================================================================================

    constexpr auto data = 0x1234;
    constexpr auto mask = 0x00f0;
    
    assert((        mask) == 0x000000f0);
    assert((data        ) == 0x00001234);
    assert((data |  mask) == 0x000012f4);
    assert((data & ~mask) == 0x00001204); 
    assert((data &  mask) == 0x00000030);
    assert((data ^  mask) == 0x000012c4);

    constexpr auto m = 0x123; assert((m << 1) == 0x246);
    constexpr auto n = -4000; assert((n >> 2) == -1000);

//  ================================================================================================

    auto x = 1, y = 2; x ^= y ^= x ^= y; // support: Google

//  ================================================================================================

    static_assert(sizeof(std::uint64_t) == 8);

    static_assert(std::is_same_v < int, std::int32_t > );

    assert(middle(0x12345678) == 0x3456);

//  ================================================================================================

    std::bitset < 8 > bitset(0b1101); // support: boost::dynamic_bitset
        
    bitset |= 0b0010; assert(bitset == 0b1111);
    bitset &= 0b0011; assert(bitset == 0b0011);

    std::cout << std::bitset < 8 > (42) << std::endl; // output: 00101010
   
    assert(std::bitset < 8 > (       42 ).to_string() == "00101010");
    assert(std::bitset < 8 > ("00101010").to_ullong() ==        42 );

//  ================================================================================================

    std::byte byte{ 42 };

    byte |= std::byte{ 0b1111'0000 }; assert(std::to_integer < int > (byte) == 0b1111'1010);
    byte &= std::byte{ 0b1111'0000 }; assert(std::to_integer < int > (byte) == 0b1111'0000);

//  ================================================================================================

    constexpr std::size_t size = 5;

    constexpr int array[size]{ 42 };

    print(std::as_bytes(std::span < const int > (array)));

//  ================================================================================================

    constexpr auto value = std::numeric_limits < unsigned int > ::max();

    const auto ptr_uint = &value;

    const auto ptr_byte = std::bit_cast < const std::byte * > (ptr_uint);

    for (std::size_t i = 0; i < sizeof(unsigned int); ++i)
    {
        assert(std::to_integer < int > (*(ptr_byte + i)) == 0xff);
    }

    assert(&array[size - 1] - &array[0] == 4);

    assert(distance_in_bytes(&array[0], &array[size - 1]) == 16);

//  ================================================================================================

    constexpr auto d = 3.14; std::uint64_t r{};

    static_assert(sizeof(d) == sizeof(r));

//  r = *reinterpret_cast < const std::uint64_t * > (&d); // bad

    r = std::bit_cast < const std::uint64_t > (d); // support: std::memcpy

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

    return 0;
}