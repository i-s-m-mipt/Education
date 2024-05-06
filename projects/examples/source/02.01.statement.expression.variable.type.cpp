#include <iostream>

int main()
{
	bool   b = true; std::cout << sizeof(b) << std::endl; // note: вывод >= 1 (Байт)
	char   c =  'a'; std::cout << sizeof(c) << std::endl; // note: вывод == 1 (Байт)
	short  s =   42; std::cout << sizeof(s) << std::endl; // note: вывод >= 2 (Байт)
	int    i =   42; std::cout << sizeof(i) << std::endl; // note: вывод >= 2 (Байт)
	long   l =   42; std::cout << sizeof(l) << std::endl; // note: вывод >= 4 (Байт)
	float  f = 3.1f; std::cout << sizeof(f) << std::endl; // note: вывод == 4 (Байт)
	double d = 3.14; std::cout << sizeof(d) << std::endl; // note: вывод == 8 (Байт)

//  ================================================================================================

	long long    ll =   42; std::cout << sizeof(ll) << std::endl; 
	long double  ld = 3.14; std::cout << sizeof(ld) << std::endl; // note: см. стандарт IEEE-754

	signed   int si =  -42; std::cout << sizeof(si) << std::endl;
	unsigned int ui =  +42; std::cout << sizeof(ui) << std::endl;

//	unsigned long long int ulli = 42ull; // bad: суффиксы напоминают венгерскую нотацию

//  ================================================================================================

	[[maybe_unused]] int m = 42, n = 42;

//	int x1; // bad: неинициализированная переменная

//	int y1 = x1; // error: неопределенное значение

	[[maybe_unused]] int  x2 = i  ;
	[[maybe_unused]] int  x3 ( i );
	[[maybe_unused]] int  x4 { i };
	[[maybe_unused]] auto x5 = i  ;

//	auto x6; // error: невозможно вывести тип из-за отсутствия инициализатора

//  ================================================================================================

//	int  y2 = d; // warning: сужающее преобразование

//	int  y3 { d }; // error: сужающее преобразование запрещено в инициализации в фигурных скобках

//	auto y4 {  int(d) }; // bad: устаревший способ

	[[maybe_unused]] auto y5 { static_cast < int > (d) };

//	auto y6 { static_cast < int > ("hello") }; // error: некорректное преобразование

	d = i = c = b;

//  ================================================================================================

	b = 0;

	std::cout << b << std::endl; // note: см. std::boolalpha

	b = static_cast < bool > (42);

	std::cout << b << std::endl; // note: см. std::boolalpha

//  ================================================================================================

	[[maybe_unused]] const auto pi = 3.14;

//	pi = 1.0; // error: константный объект

	[[maybe_unused]] volatile auto v = 42; // note: см. оптимизации компилятора

//  ================================================================================================

	using my_type = const double;

	[[maybe_unused]] my_type e = 2.72;

 //	typedef double my_old_type; // bad: устаревший способ

	[[maybe_unused]] const std::size_t size = 5;

	return 0;
}