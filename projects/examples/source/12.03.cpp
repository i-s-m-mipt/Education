///////////////////////////////////////////////////////////////////////

// chapter : Text Data Processing

///////////////////////////////////////////////////////////////////////

// content : Character Types and Literals
//
// content : Types char and wchar_t
//
// content : Types char8_t, char16_t and char32_t
//
// content : Literal Prefixes L, u8, u and U
//
// content : American Standard Code for Information Interchange (ASCII)
//
// content : Encodings ASCII 7-bit, CP1251 and CP1252
//
// content : Multibyte and Wide Encodings
//
// content : Portability Problem
//
// content : Standard Unicode
//
// content : Universal Character Set (UCS)
//
// content : Code Points and Planes
//
// content : Unicode Transformation Format (UTF)
//
// content : Encodings UTF-8, UTF-16BE, UTF-16LE and UTF-32
//
// content : Stream std::wcout

///////////////////////////////////////////////////////////////////////

// support : https://en.wikipedia.org/wiki/ASCII
//
// support : https://en.wikipedia.org/wiki/Windows-1251
//
// support : https://en.wikipedia.org/wiki/Windows-1252
//
// support : https://en.wikipedia.org/wiki/Unicode

///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <print>

///////////////////////////////////////////////////////////////////////

int main()
{
	auto x1 =   'a';

	auto x2 =  L'a';

	auto x3 = u8'a';

	auto x4 =  u'a';

	auto x5 =  U'a';

//  -------------------------------------------------

	static_assert(sizeof(x1) == 1);

	static_assert(sizeof(x2) == 4);

	static_assert(sizeof(x3) == 1);

	static_assert(sizeof(x4) == 2);

	static_assert(sizeof(x5) == 4);

//  -------------------------------------------------

	static_assert(std::is_signed_v < char    > == 1);

	static_assert(std::is_signed_v < char8_t > == 0);

//  -------------------------------------------------

	std::print("main : x1 = {}\n", x1);

//	std::print("main : x2 = {}\n", x2); // error

//	std::print("main : x3 = {}\n", x3); // error

//	std::print("main : x4 = {}\n", x4); // error

//	std::print("main : x5 = {}\n", x5); // error

//  -------------------------------------------------

	std::wcout << "main : x2 = " << x2 << '\n';
}

///////////////////////////////////////////////////////////////////////