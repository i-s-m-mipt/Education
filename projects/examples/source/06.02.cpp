///////////////////////////////////////////////////////////////////

// chapter : Projects and Libraries

///////////////////////////////////////////////////////////////////

// section : Preprocessor Directives

///////////////////////////////////////////////////////////////////

// content : Build Stages
//
// content : Preprocessing Stage
//
// content : Directive #include
//
// content : Object and Function Macros
//
// content : Directives #define and #undef
//
// content : Multi-Line Macros
//
// content : Operators ## and #
//
// content : Macro assert
//
// content : Conditional Compilation
//
// content : Directives #if, #else and #endif
//
// content : Directive #pragma

///////////////////////////////////////////////////////////////////

// support : g++ -std=с++23 -DNO_TRACE 06.02.cpp

///////////////////////////////////////////////////////////////////

#include <cassert>
#include <print>

///////////////////////////////////////////////////////////////////

#define PREFIX "test_"

///////////////////////////////////////////////////////////////////

#define FUNCTION(version) void test_##version() \
{                                               \
	std::print("{}{}\n", PREFIX, #version);     \
}

///////////////////////////////////////////////////////////////////

FUNCTION(v1) // support : compiler-explorer.com

///////////////////////////////////////////////////////////////////

#undef FUNCTION

///////////////////////////////////////////////////////////////////

// FUNCTION(v2) // error

///////////////////////////////////////////////////////////////////

#define SQUARE_v1(x) ( x  *  x )

#define SQUARE_v2(x) ((x) * (x))

///////////////////////////////////////////////////////////////////

#if defined(NO_TRACE)

#define TRACE(scope, string) ;

#else

#define TRACE(scope, string) std::print("{} : {}\n", scope, string)

#endif

///////////////////////////////////////////////////////////////////

int main()
{
	test_v1();

//	test_v2(); // error

//  -----------------------------------------------

    [[maybe_unused]] auto x = 1, y = 2;

//  -----------------------------------------------

//	assert(SQUARE_v1(x + x) == 3); // error

	assert(SQUARE_v2(x + x) == 4);

//  -----------------------------------------------

//	assert(SQUARE_v2(++x) == 6 && x == 3); // error

//	assert(SQUARE_v2(y++) == 6 && y == 4); // error

//  -----------------------------------------------

    TRACE("main", "execution ... ");

//  -----------------------------------------------

#pragma GCC diagnostic ignored "-Wsign-compare"

//  -----------------------------------------------

    assert(1u < -1);

//  -----------------------------------------------

#pragma GCC diagnostic pop
}

///////////////////////////////////////////////////////////////////