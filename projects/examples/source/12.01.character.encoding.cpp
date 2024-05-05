#include <bit>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <type_traits>

//  ================================================================================================

[[nodiscard]] inline constexpr bool is_little_endian_system() noexcept
{
	constexpr char16_t test = 0x0102;

	return (std::bit_cast < const char * > (&test))[0] == 0x02;
}

//  ================================================================================================

int main()
{
	auto c = 'a'; // note: auto -> char

	assert(static_cast < int > (c) == 97);

	assert(sizeof(char) == 1); // note: см. также std::byte

//  ================================================================================================

	std::cout << std::boolalpha << std::is_signed_v < char > << std::endl;

//	c = 255; // bad: неопределенное поведение

	for (auto i = -128; i < 128; ++i) std::cout << static_cast < char > (i) << std::endl;
	for (auto i =    0; i < 256; ++i) std::cout << static_cast < char > (i) << std::endl;

	[[maybe_unused]] constexpr   signed char sc = 'a';
	[[maybe_unused]] constexpr unsigned char uc = 'a';

//  ================================================================================================

	for (c = '!'; c <= '~'; ++c) std::cout << c;

	std::cout << std::endl;
	
	assert('8' - '0' == 8);

//  ================================================================================================

	std::cout << sizeof(wchar_t) << std::endl; // bad: проблема переносимости

	[[maybe_unused]] constexpr auto c8 = u8'a'; // note: auto -> char8_t

	assert(sizeof(char8_t) == 1); // bad: слабая поддержка в стандартной библиотеке

//  ================================================================================================

	std::cout << std::boolalpha << (std::endian::native == std::endian::little) << std::endl;

	std::cout << std::boolalpha << is_little_endian_system() << std::endl;

	return 0;
}