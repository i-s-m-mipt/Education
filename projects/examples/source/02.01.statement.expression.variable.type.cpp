#include <cassert>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <type_traits>

int main()
{
	bool   b; std::cout << "sizeof(b) = " << sizeof(b) << '\n';
	char   c; std::cout << "sizeof(c) = " << sizeof(c) << '\n';
	short  s; std::cout << "sizeof(s) = " << sizeof(s) << '\n';
	int    i; std::cout << "sizeof(i) = " << sizeof(i) << '\n';
	long   l; std::cout << "sizeof(l) = " << sizeof(l) << '\n';
	float  f; std::cout << "sizeof(f) = " << sizeof(f) << '\n';
	double d; std::cout << "sizeof(d) = " << sizeof(d) << '\n';

//  ------------------------------------------------------------------------------------------------

//	c = 'я'; // error

//	i = 2'147'483'647 + 1; // error

//	d = 1.000'000'000'000'000'123'456'789; // error

//  ------------------------------------------------------------------------------------------------

	std::cout << "std::is_signed_v < char > = " << std::boolalpha;

	std::cout <<  std::is_signed_v < char >     << '\n';

//	[[maybe_unused]]   signed           int   si; // bad
//	[[maybe_unused]]   signed      long int  sli; // bad
//	[[maybe_unused]]   signed long long int slli; // bad

	[[maybe_unused]] unsigned           int   ui;
	[[maybe_unused]] unsigned      long int  uli;
	[[maybe_unused]] unsigned long long int ulli;

	long long	ll; std::cout << "sizeof(ll) = " << sizeof(ll) << '\n';
	long double ld; std::cout << "sizeof(ld) = " << sizeof(ld) << '\n';

//  ------------------------------------------------------------------------------------------------

//	[[maybe_unused]] int x1; // bad

//	[[maybe_unused]] int x2 = x1; // error

	[[maybe_unused]] int x3{}, x4 = 1, x5(1), x6 { 1 }, x7 = { 1 };

//  ------------------------------------------------------------------------------------------------

//	[[maybe_unused]] auto y1; // error

//	[[maybe_unused]] auto y2{}; // error

	[[maybe_unused]] auto y3 = 1, y4(1), y5 { 1 };

//	[[maybe_unused]] auto y6 = { 1 }; // bad
 
	[[maybe_unused]] auto y7 = 1ull;

//	[[maybe_unused]] auto y8 = 1, y9 = 1.0; // error

//  ------------------------------------------------------------------------------------------------

//	[[maybe_unused]] int z1 = 1.0; // bad

//	[[maybe_unused]] int z2 { 1.0 }; // error

//	[[maybe_unused]] int z3 { int(1.0) }; // bad

	[[maybe_unused]] int z4 { static_cast < int > (1.0) };

//	[[maybe_unused]] int z5 { static_cast < int > ("aaaaa") }; // error

	d = i = c = b = 1; // support: cppinsights.io
	
	assert(std::abs(d - 1.0) < 1e-6);

//  ------------------------------------------------------------------------------------------------

	[[maybe_unused]] const volatile auto cvi = 1; // support: compiler-explorer.com

//	cvi = 2; // error

//  ------------------------------------------------------------------------------------------------

//	typedef const unsigned long type_alias_v1; // bad

	using type_alias_v2 = const unsigned long;

	[[maybe_unused]] type_alias_v2 cui = 1;

	[[maybe_unused]] std::size_t size_1 = 5;

	[[maybe_unused]] auto size_2 = 5uz;

//  -----------------------------------------------------

	static_assert(sizeof(std::uint16_t) == 2);
	static_assert(sizeof(std::uint32_t) == 4);
	static_assert(sizeof(std::uint64_t) == 8);
}