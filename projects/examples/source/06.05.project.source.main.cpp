#include <cassert>
#include <cstring>
#include <iostream>
#include <source_location>
#include <string>

using namespace std::literals;

#include "06.02.project.header.hpp"

#include "06.03.project.header.precompiled.hpp"

import demo;

///////////////////////////////////////////////////////////////////////////////////

#define PREFIX "test_"

#define FUNCTION(version) void test_##version() \
{                                               \
	std::cout << PREFIX << #version << '\n';    \
}                                                    

FUNCTION(v1) // support: cppinsights.io

#undef FUNCTION

//  FUNCTION(v2) // error

///////////////////////////////////////////////////////////////////////////////////

#define SQUARE_v1(x) ( x  *  x )

#define SQUARE_v2(x) ((x) * (x))

///////////////////////////////////////////////////////////////////////////////////

#if !defined(NDEBUG)

#define DEBUG(data) std::cout << __func__ << " : " << data << '\n'

#else

#define DEBUG(data) ;

#endif

///////////////////////////////////////////////////////////////////////////////////

//  void test_v2() // error
//  { 
//	    std::cout << "test_v2\n"; 
//  } 

///////////////////////////////////////////////////////////////////////////////////

namespace education
{
	namespace examples
	{
		struct Entity {};
	}
}

namespace education::examples
{
	void test(Entity)
	{
		std::cout << "education::examples::test\n";
	}
}

namespace education
{
	inline namespace library_v1
	{
		void test()
		{
			std::cout << "education::library_v1::test\n";
		}
	}

	namespace library_v2
	{
		void test()
		{
			std::cout << "education::library_v2::test\n";
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		test_v1();

		[[maybe_unused]] auto x = 1, y = 2;

//		assert(SQUARE_v1(x + x) == 3); // bad

		assert(SQUARE_v2(x + x) == 4);

//		assert(SQUARE_v2(++x) == 6 && x == 3); // error

//		assert(SQUARE_v2(y++) == 6 && y == 4); // error
	}

//  -----------------------------------------------------------------------------------

#pragma GCC diagnostic ignored "-Wunused-variable"

	{
		auto x = 1;
	}

#pragma GCC diagnostic pop

//  -----------------------------------------------------------------------------------

	{
		std::string path = __FILE__;

		auto file_name = "06.05.project.source.main.cpp";

		assert(path.substr(std::size(path) - std::strlen(file_name)) == file_name);

		assert(__LINE__ == 129);

		assert(__func__ == "main"s);

		[[maybe_unused]] auto date = __DATE__;

		[[maybe_unused]] auto time = __TIME__;

		DEBUG("trace"); // support: cppinsights.io
	}

//  ----------------------------------------------------------------------------------- 

	{
		constexpr auto source_location = std::source_location::current();

		std::string path = source_location.file_name();

		auto file_name = "06.05.project.source.main.cpp";

		assert(path.substr(std::size(path) - std::strlen(file_name)) == file_name);

		assert(source_location.line() == 143);

		assert(source_location.function_name() == "int main()"s);
	}

//  -----------------------------------------------------------------------------------

	{
		test_v2();
	
//		test_v3(); // error

//		test_v4(); // error

		test_v5();

		Entity().test();

		test_v6 < int > ();
	}

//  -----------------------------------------------------------------------------------

	{
		assert(global_x1 == 1);

//		assert(global_x2 == 2); // error

//		assert(global_x3 == 3); // error

		assert(global_x4 == 4);

		assert(global_x5 == 5);

		assert(global_x6 == 6);
	}

//  -----------------------------------------------------------------------------------

	{
		::education::examples::test(::education::examples::Entity());

		namespace ee = education::examples;

		ee::test(ee::Entity());

			test(ee::Entity());

		education::library_v1::test();

		education::library_v2::test();

		education::test();
	}

//  -----------------------------------------------------------------------------------

	{
//		using namespace std; // bad

		using namespace std::literals;

		auto string_1 = "aaaaa"s;

		auto string_2 = std::operator""s("aaaaa", 5);
	}

//  -----------------------------------------------------------------------------------

	{
		demo::test_v1();

		demo::test_v2();

//		demo::test_v3(); // error

		demo::test_v4();
	}

//  -----------------------------------------------------------------------------------

	return EXIT_SUCCESS;
}