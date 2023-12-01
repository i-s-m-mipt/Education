#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <type_traits>

constexpr std::uint16_t middle(std::uint32_t x)
{
    return (x >> 8) & 0xffff;
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
    [[maybe_unused]] auto b = 0b101010; // note: binary
    [[maybe_unused]] auto o = 052;      // note: octal
    [[maybe_unused]] auto d = 42;       // note: decimal
    [[maybe_unused]] auto x = 0x2a;     // note: hexadecimal

    std::cout << std::showbase;

    std::cout << 
        std::oct << 42 << std::endl << 
        std::dec << 42 << std::endl << 
        std::hex << 42 << std::endl;

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

    std::cout << std::boolalpha << std::is_same_v < int, std::int32_t > << std::endl;

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

    return 0;
}