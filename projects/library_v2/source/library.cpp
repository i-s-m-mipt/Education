#include <boost/dll.hpp>

#define API extern "C" BOOST_SYMBOL_EXPORT

namespace library_v2
{
	API [[nodiscard]] int test_v1(int x) 
	{ 
		return x; 
	}
}

BOOST_DLL_ALIAS(library_v2::test_v1, test_v2);