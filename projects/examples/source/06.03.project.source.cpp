#include "06.02.project.header.hpp"

#include <iostream>
#include <source_location>

//  ================================================================================================

void f()
{
	std::cout << "f from source" << std::endl;
}

//  ================================================================================================

int global_x1;

namespace
{
	[[maybe_unused]] int global_x2;

} // namespace

       const int global_y1 = 42;
extern const int global_y2 = 42;

//  ================================================================================================

#define PROMPT "Hello, "

#define FUNCTION(name) inline void generated_##name() { std::cout << PROMPT << #name << std::endl; }

FUNCTION(f)
FUNCTION(g)
FUNCTION(h)

#undef FUNCTION

#define FUNCTION 42

/*
#define BAD_SQUARE_v1(x) ( x  *  x ) // bad
#define BAD_SQUARE_v2(x) ((x) * (x)) // bad
*/

#define HAS_TRACE

#if !defined(NDEBUG) && defined(HAS_TRACE)
#  define TRACE std::cout << __FILE__ << " : " << __LINE__ << " : " << __func__ << std::endl;
#else
#  define TRACE
#endif

//  ================================================================================================

void test_macros()
{
	generated_f();
	generated_g();
	generated_h();

	std::cout << FUNCTION << std::endl;

//  ================================================================================================

	[[maybe_unused]] auto x = 42;

//	std::cout << BAD_SQUARE_v1(x + 1) << ' ' << x << std::endl; // bad
//	std::cout << BAD_SQUARE_v2(++x  ) << ' ' << x << std::endl; // bad
//	std::cout << BAD_SQUARE_v2(  x++) << ' ' << x << std::endl; // bad

//  ================================================================================================

	std::cout << __FILE__ << std::endl;
	std::cout << __LINE__ << std::endl;
	std::cout << __DATE__ << std::endl;
	std::cout << __TIME__ << std::endl;

	std::cout << __func__ << std::endl;

//  ================================================================================================

	constexpr auto location = std::source_location::current();

	std::cout << location.    file_name() << std::endl;
	std::cout << location.         line() << std::endl;
	std::cout << location.       column() << std::endl;
	std::cout << location.function_name() << std::endl;

//  ================================================================================================

	TRACE;
}

//  ================================================================================================

void C::print() const
{
	std::cout << "C::print" << std::endl;
}

//  ================================================================================================

namespace education::examples
{
	void print()
	{
		std::cout << "education::examples::print" << std::endl;
	}

	void function_with_ADL(X)
	{
		std::cout << "function_with_ADL" << std::endl;
	}

} // namespace education::examples