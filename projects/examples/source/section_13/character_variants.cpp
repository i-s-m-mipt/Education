#include <cassert>
#include <iomanip>
#include <iostream>
#include <type_traits>

int main()
{
	auto c = 'a'; // note: auto -> char

	assert(static_cast < int > (c) == 97); // note: ASCII code

	assert(sizeof(char) == 1); // note: guaranteed size 8 bits, remember std::byte

	std::cout << std::boolalpha << std::is_signed_v < char > << std::endl;

//	c = 255; // warning: overflow conversion from 255 to -1

//	const int x = c; // bad: undefined behavior, 255 or -1

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

	for (auto pc = '!'; pc <= '~'; ++pc) std::cout << pc; // note: printable ASCII characters

	std::cout << std::endl;
	
	std::cout << '8' - '0' << std::endl; // note: obtain integer digit from character digit

	std::cout << sizeof(wchar_t) << std::endl; // note: used for wide encodings on Windows, non-portable type

	assert(sizeof(char8_t )); // note: used for UTF-8  encoding
	assert(sizeof(char16_t)); // note: used for UTF-16 encoding
	assert(sizeof(char32_t)); // note: used for UTF-32 encoding

	return 0;
}