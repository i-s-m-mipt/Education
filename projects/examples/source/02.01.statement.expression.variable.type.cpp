#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>
#include <type_traits>

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::cout << "main : sizeof(bool  ) = " << sizeof(bool  ) << '\n';
		std::cout << "main : sizeof(char  ) = " << sizeof(char  ) << '\n';
		std::cout << "main : sizeof(short ) = " << sizeof(short ) << '\n';
		std::cout << "main : sizeof(int   ) = " << sizeof(int   ) << '\n';
		std::cout << "main : sizeof(long  ) = " << sizeof(long  ) << '\n';
		std::cout << "main : sizeof(float ) = " << sizeof(float ) << '\n';
		std::cout << "main : sizeof(double) = " << sizeof(double) << '\n';
	}
	
//  -----------------------------------------------------------------------------------------

	{
//		char c = 'а'; // error

//		int x = 2'147'483'647 + 1; // error

//		double y = 1.000'000'000'000'000'123'456'789; // error
	}

//  -----------------------------------------------------------------------------------------

	{
		auto is_signed_char = std::is_signed_v < char > ;

		std::cout << "main : is_signed_char = " << std::format("{}", is_signed_char) << '\n';
	}

//  -----------------------------------------------------------------------------------------
	
	{
//		[[maybe_unused]]   signed           int x1; // bad

//		[[maybe_unused]]   signed      long int x2; // bad

//		[[maybe_unused]]   signed long long int x3; // bad

		[[maybe_unused]] unsigned           int x4;

		[[maybe_unused]] unsigned      long int x5;

		[[maybe_unused]] unsigned long long int x6;

		std::cout << "main : sizeof(long double) = " << sizeof(long double) << '\n';
	}

//  -----------------------------------------------------------------------------------------

	{
//		[[maybe_unused]] int x1; // bad

//		[[maybe_unused]] int x2 = x1; // error

		[[maybe_unused]] int x3{}, x4 = 4, x5(5), x6 { 6 }, x7 = { 7 };
	}

//  -----------------------------------------------------------------------------------------

	{
//		[[maybe_unused]] auto x1; // error

//		[[maybe_unused]] auto x2{}; // error

		[[maybe_unused]] auto x3 = 3, x4(4), x5 { 5 };

//		[[maybe_unused]] auto x6 = { 6 }; // bad
 
		[[maybe_unused]] auto x7 = 7ull;

//		[[maybe_unused]] auto x8 = 8, x9 = 9.0; // error
	}

//  -----------------------------------------------------------------------------------------

	{
//		[[maybe_unused]] int x1 = 1.0; // bad

//		[[maybe_unused]] int x2 { 2.0 }; // error

//		[[maybe_unused]] int x3 { int(3.0) }; // bad

		[[maybe_unused]] int x4 { static_cast < int > (4.0) };

//		[[maybe_unused]] int x5 { static_cast < int > ("aaaaa") }; // error

		[[maybe_unused]] int x6 = 'a';
	}

//  -----------------------------------------------------------------------------------------

	{
		[[maybe_unused]] const volatile auto x = 1; // support: compiler-explorer.com

//		x = 2; // error
	}

//  -----------------------------------------------------------------------------------------

	{
//		typedef unsigned long long type_alias_v1; // bad

		using type_alias_v2 = unsigned long long;

		[[maybe_unused]] type_alias_v2 x = 1;

		[[maybe_unused]] std::size_t size_1 = 5;

		[[maybe_unused]] auto size_2 = 5uz;
	}

//  -----------------------------------------------------------------------------------------

	{
		assert(sizeof(std::int16_t) == 2 && sizeof(std::int_least16_t) >= 2);

		assert(sizeof(std::int32_t) == 4 && sizeof(std::int_least32_t) >= 4);

		assert(sizeof(std::int64_t) == 8 && sizeof(std::int_least64_t) >= 8);
	}
}