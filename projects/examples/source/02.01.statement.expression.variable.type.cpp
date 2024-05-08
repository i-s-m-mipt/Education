#include <iostream>

int main()
{
	bool   b = true; std::cout << sizeof(b) << std::endl; // output: >= 1
	char   c =  'a'; std::cout << sizeof(c) << std::endl; // output: == 1
	short  s =   42; std::cout << sizeof(s) << std::endl; // output: >= 2
	int    i =   42; std::cout << sizeof(i) << std::endl; // output: >= 2
	long   l =   42; std::cout << sizeof(l) << std::endl; // output: >= 4
	float  f = 3.14; std::cout << sizeof(f) << std::endl; // output: == 4
	double d = 3.14; std::cout << sizeof(d) << std::endl; // output: == 8

//  ================================================================================================

//	[[maybe_unused]]   signed           int s__i = 42; // bad: избыточный синтаксис
//	[[maybe_unused]]   signed      long int s_li = 42; // bad: избыточный синтаксис
//	[[maybe_unused]]   signed long long int slli = 42; // bad: избыточный синтаксис

	[[maybe_unused]] unsigned           int u__i = 42;
	[[maybe_unused]] unsigned      long int u_li = 42;
	[[maybe_unused]] unsigned long long int ulli = 42;

	[[maybe_unused]] long double ld = 3.14; // support: стандарт IEEE-754

//  ================================================================================================

	[[maybe_unused]] int m = 42, n = 42;

//	[[maybe_unused]] int  x1; // bad: неинициализированная переменная

	[[maybe_unused]] int  x2 = i  ;
	[[maybe_unused]] int  x3 ( i );
	[[maybe_unused]] int  x4 { i };

	[[maybe_unused]] auto x5 = i;

//	[[maybe_unused]] auto x6; // error

//	[[maybe_unused]] auto ull = 42ull; // bad: венгерская нотация

//  ================================================================================================

//	[[maybe_unused]] int  y1 = d; // bad: сужающее преобразование

//	[[maybe_unused]] int  y2 { d }; // error

//	[[maybe_unused]] auto y3 { int(d) }; // bad: устаревший способ

	[[maybe_unused]] auto y4 { static_cast < int > (d) };

//  ================================================================================================

	d = i = c = b; 
	
	b = 0; std::cout << b << std::endl; // output: 0
	b = i; std::cout << b << std::endl; // output: 1

//  ================================================================================================

	[[maybe_unused]] const auto pi = 3.14;

//	pi = 1.0; // error

	[[maybe_unused]] volatile auto v = 42;

//  ================================================================================================

	using my_type = const double;

	[[maybe_unused]] my_type e = 2.72;

 //	typedef double my_old_type; // bad: устаревший способ

	[[maybe_unused]] const std::size_t size = 5;

	return 0;
}