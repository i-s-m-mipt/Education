#include <iostream>

#include <boost/dll.hpp>

namespace library_v2
{
	int f(int x)
	{
		std::cout << "Hello, dynamic library!" << std::endl;

		return x;
	}

} // namespace library_v2

BOOST_DLL_ALIAS(library_v2::f, run);