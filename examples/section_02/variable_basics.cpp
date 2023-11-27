#include <iostream>

int main()
{
	bool   b = true; std::cout << sizeof(b) << std::endl; // note: 1 byte(s) usually
	char   c =  'a'; std::cout << sizeof(c) << std::endl; // note: 1 byte(s) exactly
	short  s =   42; std::cout << sizeof(s) << std::endl; // note: 2 byte(s) at least
	int    i =   42; std::cout << sizeof(i) << std::endl; // note: 2 byte(s) at least, 4 byte(s) usually
	long   l =   42; std::cout << sizeof(l) << std::endl; // note: 4 byte(s) at least
	float  f = 3.1f; std::cout << sizeof(f) << std::endl; // note: 4 byte(s) usually, single precision
	double d = 3.14; std::cout << sizeof(d) << std::endl; // note: 8 byte(s) usually, double precision

	long long   ll =   42; std::cout << sizeof(ll) << std::endl; // note: 8 byte(s) at least
	long double ld = 3.14; std::cout << sizeof(ld) << std::endl; // note: 8 byte(s) usually, can be 12 or 16 byte(s)

	[[maybe_unused]]   signed int si = 42; // note: obsolete here, int signed by default
	[[maybe_unused]] unsigned int ui = 42; // note: non-negative values, may be dangerous

	[[maybe_unused]] int variable = 0; // good: suppressed warning

//	int m = 0, n = 42; // bad: inconvenient comma separator syntax

//	int x; // bad: uninitialized variable, indeterminate value

//	int z = x; // error: undefined behavior

	[[maybe_unused]] int x1{};   // good: initialized variable, zero value
	[[maybe_unused]] int x2 = i; // good: initialized variable

	[[maybe_unused]] auto y = i; // good: type deduction

//	auto y0;   // error: invalid type deduction
//	auto y1{}; // error: invalid type deduction

//	int z0 = d; // warning: narrow conversion

//	int z1{d}; // error: prohibited narrow conversion

//	auto z2{(int)d}; // bad: old style conversion
//	auto z3{int(d)}; // bad: old style conversion

	[[maybe_unused]] auto z4{static_cast < int > (d)}; // good: new style conversion

//	auto z6{static_cast < int > ("Hello")}; // error: invalid conversion

	d = i = c = b; // good: wide conversions

	b = 0; // note: allowed narrow conversion

	std::cout << b << std::endl; // note: false outputs as 0

	b = static_cast < bool > (42);

	std::cout << b << std::endl; // note: true outputs as 1

	[[maybe_unused]] const auto pi = 3.14; // good: constant variable

//	pi = 1.0; // error: constant variable

	using my_type = const double; // good: new style type alias

	[[maybe_unused]] my_type e = 2.72;

 //	typedef double my_old_type; // bad: old style type alias

	[[maybe_unused]] const std::size_t size = 10; // good: used with arrays

	return 0;
}