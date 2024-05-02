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
	auto c = 'a'; // note: auto -> char, also used for UTF-8 support

	assert(static_cast < int > (c) == 97); // note: ASCII code

	assert(sizeof(char) == 1); // note: guaranteed size 8 bits, remember std::byte

//  ================================================================================================

	std::cout << std::boolalpha << std::is_signed_v < char > << std::endl;

//	c = 255; // bad: undefined behavior, overflow conversion from 255 to -1

	[[maybe_unused]] constexpr   signed char sc = 'a';
	[[maybe_unused]] constexpr unsigned char uc = 'a';
	
	for (auto i = -128; i < 128; ++i) // note: two's complement representation
	{
		std::cout << static_cast < char > (i);
	}

	std::cout << std::endl;

	for (auto i = 0; i < 256; ++i) // note: two's complement representation
	{
		std::cout << static_cast < char > (i);
	}

	std::cout << std::endl;

//  ================================================================================================

	for (c = '!'; c <= '~'; ++c) std::cout << c; // note: printable ASCII characters

	std::cout << std::endl;
	
	assert('8' - '0' == 8); // good: obtain integer digit from character digit

//  ================================================================================================

	[[maybe_unused]] constexpr auto c8 = u8'a'; // note: auto -> char8_t

	assert(c8 == 'a'); // note: consider char for UTF-8 for better std support

	assert(sizeof(char16_t) == 2); // note: u'a' for UTF-16, problems with support
	assert(sizeof(char32_t) == 4); // note: U'a' for UTF-32, problems with support

	std::cout << sizeof(wchar_t) << std::endl; // note: used for wide encodings on Windows

	std::cout << std::boolalpha << (std::endian::native == std::endian::little) << std::endl;

	std::cout << std::boolalpha << is_little_endian_system() << std::endl;

	return 0;
}