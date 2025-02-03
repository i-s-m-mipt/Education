#include <cassert>
#include <format>
#include <iostream>
#include <type_traits>

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		assert(sizeof(char) == 1);

		auto x = 'a';

		assert(static_cast < int > (x) == 97);

//		x = 'а'; // error

		auto is_signed_char = std::is_signed_v < char > ;

		std::cout << "main : is_signed_char = " << std::format("{}", is_signed_char) << '\n';
		
		assert('1' - '0' == 1);
	}
	
//  -----------------------------------------------------------------------------------------

	{
		std::cout << "main : sizeof(wchar_t) = " << sizeof(wchar_t) << '\n';

		auto x = L'a';

		std::wcout << "main : x = " << x << '\n';
	}

//  -----------------------------------------------------------------------------------------

	{
		assert(sizeof(char8_t) == 1);

		[[maybe_unused]] auto x = u8'a'; 	

//		std::cout << "main : x = " << x << '\n'; // error
	}	
}