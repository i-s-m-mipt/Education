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

//	[[maybe_unused]]   signed           int   si = 42; // bad
//	[[maybe_unused]]   signed      long int  sli = 42; // bad
//	[[maybe_unused]]   signed long long int slli = 42; // bad

	[[maybe_unused]] unsigned           int   ui = 42;
	[[maybe_unused]] unsigned      long int  uli = 42; // support: std::size_t
	[[maybe_unused]] unsigned long long int ulli = 42;

	[[maybe_unused]] long double ld = 3.14; // support: IEEE-754

//  ================================================================================================

//	[[maybe_unused]] int x1; // bad

	[[maybe_unused]] int x2 = i;

	[[maybe_unused]] int x3(i);

	[[maybe_unused]] int x4 { i };

	[[maybe_unused]] int x5{};

	[[maybe_unused]] int m = 42, n = 42;

//  ================================================================================================

//	[[maybe_unused]] auto y1; // error

	[[maybe_unused]] auto y2 = i;

	[[maybe_unused]] auto y3(i);

	[[maybe_unused]] auto y4 { i };

//	[[maybe_unused]] auto y5{}; // error
 
	[[maybe_unused]] auto y6 = 42ull;

//	[[maybe_unused]] auto u = 42, v = 3.14; // error

//  ================================================================================================

//	[[maybe_unused]] int z1 = d; // bad

//	[[maybe_unused]] int z2 { d }; // error

//	[[maybe_unused]] int z3 { int(d) }; // bad

	[[maybe_unused]] int z4 { static_cast < int > (d) };

//	[[maybe_unused]] int z5 { static_cast < int > ("hello") }; // error

	d = i = c = b = 42; std::cout << d << std::endl; // output: 1

//  ================================================================================================

	[[maybe_unused]] const auto pi = 3.14; // support: std::numbers::pi

//	pi = 1.0; // error

	[[maybe_unused]] volatile auto t = 42;

//  ================================================================================================

//	typedef const double type_alias_v1; // bad

	using type_alias_v2 = const double;

	[[maybe_unused]] type_alias_v2 e = 2.72; // support: std::numbers::e

	[[maybe_unused]] const std::size_t size = 5; // support: std::size

	return 0;
}