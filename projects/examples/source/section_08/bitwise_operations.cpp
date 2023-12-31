#include <bit>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <span>
#include <type_traits>

constexpr std::uint16_t middle(std::uint32_t x)
{
    return (x >> 8) & 0xffff;
}

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

template < typename T > auto distance_in_bytes(T * first, T * last)
{
    return (reinterpret_cast < char * > (last) - reinterpret_cast < char * > (first));
}

struct Datetime
{
    unsigned int milli  : 10;
    unsigned int second : 6;
    unsigned int minute : 6;
    unsigned int hour   : 5;
    unsigned int day    : 5;
    unsigned int month  : 4;
    unsigned int year   : 28; // good: 64 bits in total, no holes

}; // struct Datetime

int main()
{
    std::cout << std::showbase;

    std::cout << 
        std::oct << 42 << std::endl << 
        std::dec << 42 << std::endl << 
        std::hex << 42 << std::endl;

    [[maybe_unused]] auto b = 0b101010; // note: binary
    [[maybe_unused]] auto o = 052;      // note: octal
    [[maybe_unused]] auto d = 42;       // note: decimal
    [[maybe_unused]] auto x = 0x2a;     // note: hexadecimal

    auto data = 0x1234;
    auto mask = 0x00f0;
    
    std::cout << 
        (         mask) << std::endl << 
        ( data        ) << std::endl << 
        ( data |  mask) << std::endl << 
        ( data & ~mask) << std::endl << 
        ( data &  mask) << std::endl << 
        ( data ^  mask) << std::endl << 
        (~data        ) << std::endl;

    auto m = 0x123; assert((m << 1) == 0x246); // good: bit shift as multiplication
    auto n = -4000; assert((n >> 2) == -1000); // good: bit shift as multiplication

    static_assert(sizeof(std::uint64_t) == 8); // note: 8 byte(s) exactly

    static_assert(std::is_same_v < int, std::int32_t > );

    assert(middle(0x12345678) == 0x3456);

    std::bitset < 8 > bitset(0b1101); // note: see reference for detailed description
        
    bitset |= 0b0010; assert(bitset == 0b1111);
    bitset &= 0b0011; assert(bitset == 0b0011);

    std::cout << std::bitset < 8 > (42) << std::endl;
   
    assert(std::bitset < 8 > (        42).to_string() == "00101010");
    assert(std::bitset < 8 > ("00101010").to_ullong() ==         42);

    std::byte byte{ 42 }; // note: see reference for detailed description

    byte |= std::byte{ 0b1111'0000 }; assert(std::to_integer < int > (byte) == 0b1111'1010);
    byte &= std::byte{ 0b1111'0000 }; assert(std::to_integer < int > (byte) == 0b1111'0000);

    const std::size_t size = 10;

    int array[size]{ 42 };

    print(std::as_bytes(std::span < int > (array)));

    auto ptr_int = &x; assert(*ptr_int == 42);

    auto ptr_char = reinterpret_cast < char * > (ptr_int); // note: very dangerous

    std::cout << *ptr_char << std::endl;

    assert(&array[size - 1] - &array[0] == 9); // note: pointer arithmetic

    assert(distance_in_bytes(&array[0], &array[size - 1]) == 36);

    return 0;
}