#include <bit>
#include <cassert>
#include <ios>
#include <iostream>
#include <type_traits>

int main()
{
	auto c = 'a';

	assert(static_cast < int > (c) == 97);

	assert(sizeof(char) == 1); // support: std::byte

//  ================================================================================================

	std::cout << std::boolalpha << std::is_signed_v < char > << std::endl;

//	c = 255; // error
	
	for (auto i = 0; i < 256; ++i) 
	{
		std::cout << static_cast < char > (i);

		if ((i + 1) % 64 == 0) 
		{
			std::cout << '\n';
		}
	}

	std::cout << std::endl;

	[[maybe_unused]]   signed char sc = 'a';
	[[maybe_unused]] unsigned char uc = 'a';

//  ================================================================================================

	for (c = '!'; c <= '~'; ++c) 
	{
		std::cout << c;
	}

	std::cout << std::endl;
	
	assert('8' - '0' == 8);

//  ================================================================================================

//	wchar_t wc = L'a'; // bad

	std::cout << sizeof(wchar_t) << std::endl;

	auto c8 = u8'a'; c = c8; // support: UTF-8

//  ================================================================================================

	auto x = static_cast < char16_t > (0x1234);

	auto is_little_endian_1 = *std::bit_cast < char * > (&x) == 0x34;

	std::cout << std::boolalpha << "is_little_endian_1 = " << is_little_endian_1 << '\n';

	auto is_little_endian_2 = std::endian::native == std::endian::little;

	std::cout << std::boolalpha << "is_little_endian_2 = " << is_little_endian_2 << '\n';
}