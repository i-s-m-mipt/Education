#include "project_header.hpp"

#include <iostream>
#include <source_location>

void f() // note: definition, external linkage
{
	std::cout << "f from source" << std::endl;
}

// =================================================================================================

int global_x1; // note: zero value initialization, external linkage

namespace // note: anonymous namespace
{
	[[maybe_unused]] int global_x2; // note: internal linkage

} // namespace

       const int global_y1 = 42; // note: internal linkage
extern const int global_y2 = 42; // note: external linkage

// =================================================================================================

#define PROMPT "Hello, " // note: object-like macros with substitution text

#define FUNCTION(name) inline void generated_##name() \
{ std::cout << PROMPT << #name << std::endl; }

FUNCTION(f)
FUNCTION(g)
FUNCTION(h)

#undef FUNCTION // note: be careful when undef outer macros

#define FUNCTION 42 // note: redefined macro as object-like

//#define BAD_SQUARE(x) (x * x) // bad: incorrect computation

//#define SQUARE(x) ((x) * (x)) // bad: dangerous side effect

#define HAS_TRACE // note: object-like macros without substitution text

#if defined(_DEBUG) && defined(HAS_TRACE) // note: _DEBUG is a preset macro in Visual Studio
#  define TRACE std::cout << __FILE__ << ':' << __LINE__ << ':' << __func__ << std::endl
#else
#  define TRACE // good: nothing to do in release mode
#endif

void test_macros()
{
	generated_f();
	generated_g();
	generated_h();

	std::cout << FUNCTION << std::endl; // note: redefined as number

	[[maybe_unused]] auto x = 1;

//	std::cout << BAD_SQUARE(x + 1) << std::endl; // bad: incorrect macro

//	std::cout << SQUARE(x++) << ' ' << x << std::endl; // bad: dangerous side effect
//	std::cout << SQUARE(++x) << ' ' << x << std::endl; // bad: dangerous side effect

	std::cout << __FILE__ << std::endl; // good: useful macro
	std::cout << __LINE__ << std::endl; // good: useful macro
	std::cout << __DATE__ << std::endl; // good: useful macro
	std::cout << __TIME__ << std::endl; // good: useful macro

	std::cout << __func__ << std::endl; // note: implicit local array with function name

	constexpr auto location = std::source_location::current(); // good: macros alternative

	std::cout << location.    file_name() << std::endl;
	std::cout << location.         line() << std::endl;
	std::cout << location.       column() << std::endl;
	std::cout << location.function_name() << std::endl;

	TRACE; // good: semicolon at end
}

// =================================================================================================

void C::print() const // good: member function definition in source file
{
	std::cout << "C::print" << std::endl;
}

namespace education::examples // note: namespaces additivity
{
	void print()
	{
		std::cout << "education::examples::print" << std::endl;
	}

	void function_with_ADL(X)
	{
		std::cout << "argument-dependent lookup" << std::endl;
	}

} // namespace education::examples