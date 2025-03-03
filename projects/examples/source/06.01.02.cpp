#include <cassert>
#include <iostream>

//////////////////////////////////////////////////////////////////////////

#define PREFIX "test_"

#define FUNCTION(version) void test_##version() \
{                                               \
	std::cout << PREFIX << #version << '\n';    \
}                                                    

FUNCTION(v1) // support: cppinsights.io

#undef FUNCTION

//  FUNCTION(v2) // error

//////////////////////////////////////////////////////////////////////////

#define SQUARE_v1(x) ( x  *  x )

#define SQUARE_v2(x) ((x) * (x))

//////////////////////////////////////////////////////////////////////////

#if defined(NO_TRACE)

#define TRACE(scope, string) ;

#else

#define TRACE(scope, string) std::cout << scope << " : " << string << '\n'

#endif

//////////////////////////////////////////////////////////////////////////

int main()
{
	test_v1();

//  -----------------------------------------------

#pragma GCC diagnostic ignored "-Wunused-variable"

    auto x = 1, y = 2;

#pragma GCC diagnostic pop

//  -----------------------------------------------

//	assert(SQUARE_v1(x + x) == 3); // bad

//  -----------------------------------------------

	assert(SQUARE_v2(x + x) == 4);

//  -----------------------------------------------

//	assert(SQUARE_v2(++x) == 6 && x == 3); // error

//	assert(SQUARE_v2(y++) == 6 && y == 4); // error

//  -----------------------------------------------

    TRACE("main", "trace");
}