////////////////////////////////////////////////

// support : en.wikipedia.org/wiki/ASCII
//
// support : en.wikipedia.org/wiki/Windows-1251
//
// support : en.wikipedia.org/wiki/Windows-1252

////////////////////////////////////////////////

#include <iostream>
#include <print>

////////////////////////////////////////////////

int main()
{	
	auto x1 =   'a'; 
	
	auto x2 =  L'a';
	
	auto x3 = u8'a';
	
	auto x4 =  u'a';
	
	auto x5 =  U'a';

//  --------------------------------------------

	static_assert(sizeof(x1) == 1);

	static_assert(sizeof(x2) == 4);

	static_assert(sizeof(x3) == 1);

	static_assert(sizeof(x4) == 2);

	static_assert(sizeof(x5) == 4);

//  --------------------------------------------

	std::print("main : x1 = {}\n", x1);

//	std::print("main : x2 = {}\n", x2); // error

//	std::print("main : x3 = {}\n", x3); // error

//	std::print("main : x4 = {}\n", x4); // error

//	std::print("main : x5 = {}\n", x5); // error
	
//  --------------------------------------------

	std::wcout << "main : x2 = " << x2 << '\n';
}

////////////////////////////////////////////////