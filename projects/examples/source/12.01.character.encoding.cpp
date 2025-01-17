#include <cassert>
#include <format>
#include <iostream>
#include <type_traits>

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		assert(sizeof(char) == 1);

		auto c = 'a';

		assert(static_cast < int > (c) == 97);

//		c = 'а'; // error

		auto is_signed_char = std::is_signed_v < char > ;

		std::cout << "main : is_signed_char = " << std::format("{}", is_signed_char) << '\n';
		
		assert('1' - '0' == 1);
	}
	
//  -----------------------------------------------------------------------------------------

	{
		std::cout << "main : sizeof(wchar_t) = " << sizeof(wchar_t) << '\n';

		auto wc = L'a';

		std::wcout << "wc = " << wc << '\n';
	}

//  -----------------------------------------------------------------------------------------

	{
		assert(sizeof(char8_t) == 1);

		[[maybe_unused]] auto c8 = u8'a'; 	

//		std::cout << "main : c8 = " << c8 << '\n'; // error
	}	
}