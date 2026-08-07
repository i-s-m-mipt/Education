////////////////////////////////////////////////////////////////////////////////

// chapter : Projects and Libraries

////////////////////////////////////////////////////////////////////////////////

// content : Libraries
//
// content : Static and Dynamic Libraries
//
// content : Library Boost.Dll
//
// content : Wrapper std::function
//
// content : Implicit and Explicit Dynamic Linking
//
// content : Tools ldd, readelf, grep, ltrace and strace
//
// content : Executable and Linkable Format (ELF)
//
// content : Relocatable, Executable and Shared Object Files
//
// content : The Boost C++ Library Collection
//
// content : System CMake

////////////////////////////////////////////////////////////////////////////////

// support : ldd ./06.17
//
// support : readelf --dynamic ./06.17 | grep NEEDED
//
// support : ltrace ./06.17
//
// support : strace ./06.17

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

#include <boost/dll.hpp>

////////////////////////////////////////////////////////////////////////////////

#include "06.18.hpp"

////////////////////////////////////////////////////////////////////////////////

int main()
{
	library::test();

//  ----------------------------------------------------------------------------

	std::vector < std::function < void() > > functions;

//  ----------------------------------------------------------------------------

	auto path = "libshared.so";

//  ----------------------------------------------------------------------------

	functions.push_back(boost::dll::import_symbol < void() > (path, "test_v1"));

	functions.push_back(boost::dll::import_symbol < void() > (path, "test_v2"));

//  ----------------------------------------------------------------------------

	for (auto const & function : functions)
	{
		function();
	}

//  ----------------------------------------------------------------------------

	boost::dll::import_alias < void() > (path, "test_v3")();
}

////////////////////////////////////////////////////////////////////////////////