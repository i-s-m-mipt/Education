#include <iostream>

#include <boost/dll.hpp>

/////////////////////////////////////////////////////////////

#define API extern "C" BOOST_SYMBOL_EXPORT

/////////////////////////////////////////////////////////////

namespace library
{
	API void test_v1() { std::cout << "library::test_v1\n"; }
	
	API void test_v2() { std::cout << "library::test_v2\n"; }
}

/////////////////////////////////////////////////////////////

BOOST_DLL_ALIAS(library::test_v2, test_v3);