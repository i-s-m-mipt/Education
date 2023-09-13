#include <iostream>

int main()
{
	bool   b = true;
	char   c =  'a';
	int    i =   42;
	double d = 3.14;

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
//	int z1{d};  // error: prohibited narrow conversion

//	auto z2{(int)d}; // bad: old style conversion
//	auto z3{int(d)}; // bad: old style conversion

	[[maybe_unused]] auto z4{static_cast < int > (d)}; // good: new style conversion

//	auto z6{static_cast < int > ("Hello")}; // error: invalid conversion

	d = i = c = b; // good: wide conversions

	b = 0; // note: allowed narrow conversion

	std::cout << b << '\n'; // note: false outputs as 0

	b = static_cast < bool > (42);

	std::cout << b << '\n'; // note: true outputs as 1

	[[maybe_unused]] const auto pi = 3.14; // good: constant variable

	using my_type = const double; // good: new style type alias

	[[maybe_unused]] my_type e = 2.72;

	typedef double my_old_type; // bad: old style type alias

	return 0;
}