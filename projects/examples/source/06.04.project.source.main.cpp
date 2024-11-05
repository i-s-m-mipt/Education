#include "06.06.project.header.precompiled.hpp"

#include <cassert>
#include <cstring>
#include <iostream>
#include <source_location>
#include <string>

using namespace std::literals;

#include "06.02.project.header.hpp"

import demo;

//  ================================================================================================

//  void test_v1() // error
//  { 
//	    std::clog << "test_v1\n"; 
//  } 

//  ================================================================================================

#define PREFIX "test_"

#define FUNCTION(name) void test_##name() \
{                                         \
	std::clog << PREFIX << #name << '\n'; \
}                                                    

FUNCTION(v6) // support: cppinsights.io

#undef FUNCTION

//  ================================================================================================

//  #define SQUARE_v1(x) ( x  *  x ) // bad
//  #define SQUARE_v2(x) ((x) * (x)) // bad

//  ================================================================================================

#if !defined(NDEBUG)

#define TRACE std::cout << __FILE__ << " : "; \
			  std::cout << __LINE__ << " : "; \
			  std::cout << __func__ << " : "

#endif

//  ================================================================================================

int main()
{
	test_v1();
	
//	test_v2(); // error

//	test_v3(); // error

	test_v4();

	test_v5 < Entity_v1 > ();

//  -------------------------

	Entity_v1::test_v1();
	Entity_v1::test_v2();

//  ---------------------

	test_v6();

	[[maybe_unused]] auto x = 1;

//	assert(SQUARE_v1(x + x) == 3); // bad

//	assert(SQUARE_v2(x++) == 2 && x == 3); // error

//  -----------------------------------------------

	std::string string_1 = __FILE__;

	auto path = "06.04.project.source.main.cpp";

	auto size = std::strlen(path);

	assert(string_1.substr(std::size(string_1) - size, size) == path);

	assert(__LINE__ == 89);

	assert(std::string(__func__) == "main");

	std::cout << "__DATE__ = " << __DATE__ << '\n';
	std::cout << "__TIME__ = " << __TIME__ << '\n';

	TRACE << "trace\n"; // support: cppinsights.io

//  ----------------------------------------------------------

	constexpr auto location = std::source_location::current();

	std::string string_2 = location.file_name();

	assert(string_2.substr(std::size(string_2) - size, size) == path);

	assert(location.line() == 100 && location.column() == 57);

	assert(std::string(location.function_name()) == "int main()");

//  --------------------------------------------------------------

	assert(global_x1 == 1);
//	assert(global_x2 == 2); // error
//	assert(global_x3 == 3); // error
	assert(global_x4 == 4);

//  ----------------------------------------------------------------

	::education::examples::test(::education::examples::Entity_v2());

	namespace ee = education::examples;

	ee::test(ee::Entity_v2());
		test(ee::Entity_v2());

//	using namespace std; // bad

	using namespace std::literals;

	using std::cout;

//  --------------------------------------

	assert(invoke(demo::test_v1, 1) == 1);
	assert(invoke(demo::test_v2, 1) == 1);
	assert(invoke(demo::test_v3, 1) == 1);

//  --------------------------------------

	return EXIT_SUCCESS;
}