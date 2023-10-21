#include <iostream>

#include <boost/dll.hpp>

namespace library_v2
{
	int f(int value)
	{
		std::cout << "Hello, dynamic library!" << std::endl;

		return value;
	}

} // namespace library_v2

BOOST_DLL_ALIAS(library_v2::f, run);