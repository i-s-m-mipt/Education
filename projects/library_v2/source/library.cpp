#include <iostream>

#include <boost/dll.hpp>

#define API extern "C" BOOST_SYMBOL_EXPORT

namespace library_v2
{
	API void test_v1() 
	{ 
		std::clog << "library_v2::test_v1\n"; 
	}
}

BOOST_DLL_ALIAS(library_v2::test_v1, test_v2);