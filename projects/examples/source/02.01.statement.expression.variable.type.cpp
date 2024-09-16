#include <cassert>
#include <cmath>

int main()
{
	[[maybe_unused]] bool   b {}; assert(sizeof(b) >= 1);
	[[maybe_unused]] char   c {}; assert(sizeof(c) == 1);
	[[maybe_unused]] short  s {}; assert(sizeof(s) >= 2);
	[[maybe_unused]] int    i {}; assert(sizeof(i) >= 2);
	[[maybe_unused]] long   l {}; assert(sizeof(l) >= 4);
	[[maybe_unused]] float  f {}; assert(sizeof(f) == 4);
	[[maybe_unused]] double d {}; assert(sizeof(d) == 8);

//  ================================================================================================

//	[[maybe_unused]]   signed           int   si {}; // bad
//	[[maybe_unused]]   signed      long int  sli {}; // bad
//	[[maybe_unused]]   signed long long int slli {}; // bad

	[[maybe_unused]] unsigned           int   ui {};
	[[maybe_unused]] unsigned      long int  uli {};
	[[maybe_unused]] unsigned long long int ulli {};

	[[maybe_unused]] long double ld {}; assert(sizeof(ld) >= 8);

//  ================================================================================================

//	[[maybe_unused]] int x1; // bad

	[[maybe_unused]] int x2 = 1, x3(1), x4 { 1 }, x5{};

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

//	[[maybe_unused]] int z5 { static_cast < int > ("hello") }; // error

	d = i = c = b = 1; assert(std::abs(d - 1.0) < 0.000001);

//  ================================================================================================

	[[maybe_unused]] const volatile auto cvi = 1;

//	cvi = 2; // error

//  ================================================================================================

//	typedef const double type_alias_v1; // bad

	using type_alias_v2 = const double;

	[[maybe_unused]] type_alias_v2 cd = 1.0;

	[[maybe_unused]] const std::size_t size = 5;

	return 0;
}