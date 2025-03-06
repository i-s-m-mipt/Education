#include <functional>
#include <vector>

#include <boost/dll.hpp>

#include "06.03.02.hpp"

////////////////////////////////////////////////////////////////////////////////

int main()
{
	library::test();

//  ----------------------------------------------------------------------------

	auto path = "libshared.so";

//  ----------------------------------------------------------------------------

	std::vector < std::function < void() > > functions;

//  ----------------------------------------------------------------------------

	functions.push_back(boost::dll::import_symbol < void() > (path, "test_v1"));

	functions.push_back(boost::dll::import_symbol < void() > (path, "test_v2"));

//  ----------------------------------------------------------------------------
		
	for (const auto & function : functions)
	{
		function();
	}

//  ----------------------------------------------------------------------------

	boost::dll::import_alias < void() > (path, "test_v3")();
}