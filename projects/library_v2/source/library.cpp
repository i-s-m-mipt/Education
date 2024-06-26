#include <iostream>

#include <boost/dll.hpp>

#define API extern "C" BOOST_SYMBOL_EXPORT

namespace library_v2
{
	API [[nodiscard]] int f(int x)
	{
		std::cout << "Hello, dynamic library!" << std::endl;

		return x;
	}

	API int global_variable;

	[[nodiscard]] int g(int x) { return x; }

} // namespace library_v2

int library_v2::global_variable = 42;

BOOST_DLL_ALIAS(library_v2::g, run);