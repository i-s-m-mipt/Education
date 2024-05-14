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
	auto c = 'a';

	assert(static_cast < int > (c) == 97);

	assert(sizeof(char) == 1); // support: std::byte

//  ================================================================================================

	std::cout << std::boolalpha << std::is_signed_v < char > << std::endl;

//	c = 255; // error
	
	for (auto i = 0; i < 256; ++i) 
	{
		std::cout << static_cast < char > (i);

		if ((i + 1) % 64 == 0) std::cout << std::endl;
	}

	std::cout << std::endl;

	[[maybe_unused]] constexpr   signed char sc = 'a';
	[[maybe_unused]] constexpr unsigned char uc = 'a';

//  ================================================================================================

	for (c = '!'; c <= '~'; ++c) std::cout << c;

	std::cout << std::endl;
	
	assert('8' - '0' == 8);

//  ================================================================================================

//	constexpr wchar_t wc = L'a'; // bad

	std::cout << sizeof(wchar_t) << std::endl;

	constexpr auto c8 = u8'a'; // detail: char8_t

	c = c8; // support: UTF-8

//  ================================================================================================

	std::cout << std::boolalpha << (std::endian::native == std::endian::little) << std::endl;

	std::cout << std::boolalpha << is_little_endian_system() << std::endl;

	return 0;
}