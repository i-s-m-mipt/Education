#include <iostream>

int main()
{
	bool   b = true; std::cout << sizeof(b) << std::endl; // output: >= 1
	char   c =  'a'; std::cout << sizeof(c) << std::endl; // output: == 1
	short  s =   42; std::cout << sizeof(s) << std::endl; // output: >= 2
	int    i =   42; std::cout << sizeof(i) << std::endl; // output: >= 2
	long   l =   42; std::cout << sizeof(l) << std::endl; // output: >= 4
	float  f = 3.1f; std::cout << sizeof(f) << std::endl; // output: == 4
	double d = 3.14; std::cout << sizeof(d) << std::endl; // output: == 8

//  ================================================================================================

//	[[maybe_unused]]   signed int si = -42; // bad: избыточный синтаксис
	[[maybe_unused]] unsigned int ui = +42;

	[[maybe_unused]] long double ld = 3.14; // support: стандарт IEEE-754

//	[[maybe_unused]] unsigned long long ull = 42ull; // bad: плохой стиль

//  ================================================================================================

	[[maybe_unused]] int m = 42, n = 42;

//	[[maybe_unused]] int x1; // bad: неинициализированная переменная

//	i = x1; // warning

	[[maybe_unused]] int  x2 = i  ;
	[[maybe_unused]] int  x3 ( i );
	[[maybe_unused]] int  x4 { i };

	[[maybe_unused]] auto x5 = i;
//	[[maybe_unused]] auto x6; // error

//  ================================================================================================

//	[[maybe_unused]] int  y1 = d  ; // bad: сужающее преобразование
//	[[maybe_unused]] int  y2 { d }; // error

//	[[maybe_unused]] auto y3 {  int(d) }; // bad: устаревший способ
//	[[maybe_unused]] auto y4 { (int)d  }; // bad: устаревший способ

	[[maybe_unused]] auto y5 { static_cast < int > (      d) };
//	[[maybe_unused]] auto y6 { static_cast < int > ("hello") }; // error

//  ================================================================================================

	d = i = c = b; b = 0; b = static_cast < bool > (i);

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