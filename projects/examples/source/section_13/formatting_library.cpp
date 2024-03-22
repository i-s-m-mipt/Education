#include <format>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
    std::cout << std::format("Answer is {}", 42) << std::endl; // note: Python formatting

    std::string buffer;

    std::format_to(std::back_inserter(buffer), "Answer is {}", 42); // note: format_to_n

    std::cout << buffer << std::endl;

    std::cout << std::format("{0}, {1}!", "Hello", "world") << std::endl;

    std::cout << std::format("{:_<8}", 42) << std::endl; // note: L-shift
    std::cout << std::format("{:_>8}", 42) << std::endl; // note: R-shift
    std::cout << std::format("{:_^8}", 42) << std::endl; // note: C-shift

    std::cout << std::format("{:08b}", 42) << std::endl; // note: binary
    std::cout << std::format("{:08o}", 42) << std::endl; // note: octal
    std::cout << std::format("{:08d}", 42) << std::endl; // note: decimal
    std::cout << std::format("{:08x}", 42) << std::endl; // note: hexadecimal

    constexpr auto d = 0.123456789;

    std::cout << std::format("{:.5}", d) << std::endl; // note: 5 digits of precision

    return 0;
}