#include <cassert>
#include <ios>
#include <iostream>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	assert(sizeof(char) == 1);

	auto c = 'a';

	assert(static_cast < int > (c) == 97);

//	c = 'я'; // error

	auto is_char_signed = std::is_signed_v < char > ;

	std::cout << "main : is_char_signed = " << std::boolalpha << is_char_signed << '\n';
	
	assert('1' - '0' == 1);

//  ------------------------------------------------------------------------------------

	std::cout << "main : sizeof(wchar_t) = " << sizeof(wchar_t) << '\n';

	auto wc = L'a';

	std::wcout << "wc = " << wc << '\n';

//  ------------------------------------------------------------------------------------

	assert(sizeof(char8_t) == 1);

	[[maybe_unused]] auto c8 = u8'a'; 	

//	std::cout << "main : c8 = " << c8 << '\n'; // error
}