#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "main : sizeof(bool  ) = " << sizeof(bool  ) << '\n';
	std::cout << "main : sizeof(char  ) = " << sizeof(char  ) << '\n';
	std::cout << "main : sizeof(short ) = " << sizeof(short ) << '\n';
	std::cout << "main : sizeof(int   ) = " << sizeof(int   ) << '\n';
	std::cout << "main : sizeof(long  ) = " << sizeof(long  ) << '\n';
	std::cout << "main : sizeof(float ) = " << sizeof(float ) << '\n';
	std::cout << "main : sizeof(double) = " << sizeof(double) << '\n';

//  ------------------------------------------------------------------------------------

//	char c = 'а'; // error

//	int i = 2'147'483'647 + 1; // error

//	double d = 1.000'000'000'000'000'123'456'789; // error

//  ------------------------------------------------------------------------------------

	auto is_signed_char = std::is_signed_v < char > ;

	std::cout << "main : is_signed_char = " << std::format("{}", is_signed_char) << '\n';

//	[[maybe_unused]]   signed           int   si; // bad
//	[[maybe_unused]]   signed      long int  sli; // bad
//	[[maybe_unused]]   signed long long int slli; // bad

	[[maybe_unused]] unsigned           int   ui;
	[[maybe_unused]] unsigned      long int  uli;
	[[maybe_unused]] unsigned long long int ulli;

	std::cout << "main : sizeof(long double) = " << sizeof(long double) << '\n';

//  ------------------------------------------------------------------------------------

//	[[maybe_unused]] int x1; // bad

//	[[maybe_unused]] int x2 = x1; // error

	[[maybe_unused]] int x3{}, x4 = 1, x5(1), x6 { 1 }, x7 = { 1 };

//  ------------------------------------------------------------------------------------

//	[[maybe_unused]] auto y1; // error

//	[[maybe_unused]] auto y2{}; // error

	[[maybe_unused]] auto y3 = 1, y4(1), y5 { 1 };

//	[[maybe_unused]] auto y6 = { 1 }; // bad
 
	[[maybe_unused]] auto y7 = 1ull;

//	[[maybe_unused]] auto y8 = 1, y9 = 1.0; // error

//  ------------------------------------------------------------------------------------

//	[[maybe_unused]] int z1 = 1.0; // bad

//	[[maybe_unused]] int z2 { 1.0 }; // error

//	[[maybe_unused]] int z3 { int(1.0) }; // bad

	[[maybe_unused]] int z4 { static_cast < int > (1.0) };

//	[[maybe_unused]] int z5 { static_cast < int > ("aaaaa") }; // error

//  ------------------------------------------------------------------------------------

	[[maybe_unused]] const volatile auto cvi = 1; // support: compiler-explorer.com

//	cvi = 2; // error

//  ------------------------------------------------------------------------------------

//	typedef unsigned long long type_alias_v1; // bad

	using type_alias_v2 = unsigned long long;

	[[maybe_unused]] type_alias_v2 ull = 1;

	[[maybe_unused]] std::size_t size_1 = 5;

	[[maybe_unused]] auto size_2 = 5uz;

//  ------------------------------------------------------------------------------------

	assert(sizeof(std::int16_t) == 2 && sizeof(std::int_least16_t) >= 2);
	assert(sizeof(std::int32_t) == 4 && sizeof(std::int_least32_t) >= 4);
	assert(sizeof(std::int64_t) == 8 && sizeof(std::int_least64_t) >= 8);
}