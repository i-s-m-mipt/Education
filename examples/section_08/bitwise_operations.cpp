#include <cstdint>
#include <iostream>

std::uint16_t middle(std::uint32_t x)
{
    return (x >> 8) & 0xffff;
}

int main()
{
    auto d = 42;
    auto o = 052;
    auto x = 0x2a;
    auto b = 0b101010;

    

    std::cout << std::oct << 42 << std::endl
              << std::dec << 42 << std::endl
              << std::hex << 42 << std::endl;

    std::cout << sizeof(std::uint64_t) << std::endl;

    std::cout << std::boolalpha << std::is_same_v < int, std::int32_t > << std::endl;

    std::uint16_t mask = 0x00f0;
    std::uint32_t value = 0x12345678;

    std::cout << std::hex << std::showbase
        << mask << std::endl
        << value << std::endl
        << (value | mask) << std::endl
        << (value & ~mask) << std::endl
        << (value & mask) << std::endl
        << (value ^ mask) << std::endl
        << (~value) << std::endl;

    auto v1 = 0x123;

    std::cout << (v1 << 1) << std::endl;

    auto v2 = -1000;

    std::cout << std::dec << (v2 >> 2) << std::endl;

    bitset, std::byte, bits, bit fields

    return 0;
}