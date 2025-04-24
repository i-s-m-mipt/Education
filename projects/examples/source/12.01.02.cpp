////////////////////////////////////////////////////////

// support : en.wikipedia.org/wiki/ASCII

////////////////////////////////////////////////////////

// support : en.wikipedia.org/wiki/Windows-1251

// support : en.wikipedia.org/wiki/Windows-1252

////////////////////////////////////////////////////////

#include <iostream>

////////////////////////////////////////////////////////

int main()
{	
	auto x1 =   'a'; 
	
	auto x2 =  L'a';
	
	auto x3 = u8'a';
	
	auto x4 =  u'a';
	
	auto x5 =  U'a';

//  ----------------------------------------------------

	static_assert(sizeof(x1) == 1);

	static_assert(sizeof(x2) == 4);

	static_assert(sizeof(x3) == 1);

	static_assert(sizeof(x4) == 2);

	static_assert(sizeof(x5) == 4);

//  ----------------------------------------------------

	std:: cout << "main : x1 = " << x1 << '\n';
	
	std::wcout << "main : x2 = " << x2 << '\n';

//	std:: cout << "main : x3 = " << x3 << '\n'; // error

//	std:: cout << "main : x4 = " << x4 << '\n'; // error

//	std:: cout << "main : x5 = " << x5 << '\n'; // error
}

////////////////////////////////////////////////////////