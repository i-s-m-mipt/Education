#include <cassert>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <type_traits>

int main()
{
	bool   b{}; std::cout << "sizeof(b) = " << sizeof(b) << std::endl;
	char   c{}; std::cout << "sizeof(c) = " << sizeof(c) << std::endl;
	short  s{}; std::cout << "sizeof(s) = " << sizeof(s) << std::endl;
	int    i{}; std::cout << "sizeof(i) = " << sizeof(i) << std::endl;
	long   l{}; std::cout << "sizeof(l) = " << sizeof(l) << std::endl;
	float  f{}; std::cout << "sizeof(f) = " << sizeof(f) << std::endl;
	double d{}; std::cout << "sizeof(d) = " << sizeof(d) << std::endl;

//  ================================================================================================

//	c = 'я'; // error

//	i = 2'147'483'647 + 1; // error

//	d = 1.000'000'000'000'000'123'456'789; // error

//  ================================================================================================

	std::cout << "std::is_signed_v < char > = " << std::boolalpha;

	std::cout <<  std::is_signed_v < char >     << std::endl;

//	[[maybe_unused]]   signed           int   si{}; // bad
//	[[maybe_unused]]   signed      long int  sli{}; // bad
//	[[maybe_unused]]   signed long long int slli{}; // bad

	[[maybe_unused]] unsigned           int   ui{};
	[[maybe_unused]] unsigned      long int  uli{};
	[[maybe_unused]] unsigned long long int ulli{};

	long long	ll{}; std::cout << "sizeof(ll) = " << sizeof(ll) << std::endl;
	long double ld{}; std::cout << "sizeof(ld) = " << sizeof(ld) << std::endl;

//  ================================================================================================

//	[[maybe_unused]] int x1; // bad

//	[[maybe_unused]] int x2 = x1; // error

	[[maybe_unused]] int x3 = 1, x4(1), x5 { 1 }, x6{};

//  ================================================================================================

//	[[maybe_unused]] auto y1; // error

	[[maybe_unused]] auto y2 = 1, y3(1), y4 { 1 };

//	[[maybe_unused]] auto y5{}; // error
 
	[[maybe_unused]] auto y6 = 1ull;

//	[[maybe_unused]] auto y7 = 1, y8 = 1.0; // error

//  ================================================================================================

//	[[maybe_unused]] int z1 = 1.0; // bad

//	[[maybe_unused]] int z2 { 1.0 }; // error

//	[[maybe_unused]] int z3 { int(1.0) }; // bad

	[[maybe_unused]] int z4 { static_cast < int > (1.0) };

//	[[maybe_unused]] int z5 { static_cast < int > ("aaa") }; // error

	d = i = c = b = 1; // support: cppinsights.io
	
	assert(std::abs(d - 1.0) < 0.000'001);

//  ================================================================================================

	[[maybe_unused]] const volatile auto cvi = 1; // support: compiler-explorer.com

//	cvi = 2; // error

//  ================================================================================================

//	typedef const double type_alias_v1; // bad

	using type_alias_v2 = const double;

	[[maybe_unused]] type_alias_v2 cd = 1.0;

	[[maybe_unused]] const std::size_t size = 5;

	std::uint16_t ui16{}; assert(sizeof(ui16) == 2);
	std::uint32_t ui32{}; assert(sizeof(ui32) == 4);
	std::uint64_t ui64{}; assert(sizeof(ui64) == 8);

	return 0;
}