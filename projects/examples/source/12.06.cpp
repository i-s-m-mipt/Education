/////////////////////////////////////////////////////////////////////

// chapter : Characters

/////////////////////////////////////////////////////////////////////

// content : Strings
//
// content : Strings std::string and std::wstring
//
// content : Strings std::u8string, std::u16string and std::u32string
//
// content : Literal Prefixes L, u8, u and U
//
// content : Operator ""s
//
// content : Namespace std::literals
//
// content : God Class Problem

/////////////////////////////////////////////////////////////////////

// support : Boost.StringAlgorithms

/////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <print>
#include <string>

/////////////////////////////////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////////////////////////////////

int main()
{
    auto string_1 =   "aaaaa"s;

    auto string_2 =  L"aaaaa"s;

    auto string_3 = u8"aaaaa"s;

    auto string_4 =  u"aaaaa"s;

    auto string_5 =  U"aaaaa"s;

//  --------------------------------------------------------

    std::print("main : string_1 = {}\n", string_1);

//	std::print("main : string_2 = {}\n", string_2); // error

//	std::print("main : string_3 = {}\n", string_3); // error

//	std::print("main : string_4 = {}\n", string_4); // error

//	std::print("main : string_5 = {}\n", string_5); // error

//  --------------------------------------------------------

	std::wcout << "main : string_2 = " << string_2 << '\n';

//  --------------------------------------------------------

    assert(string_1.find('a') != std::string::npos);
}

/////////////////////////////////////////////////////////////////////