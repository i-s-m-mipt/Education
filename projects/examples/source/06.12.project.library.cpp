#include <cassert>

#include <boost/dll.hpp>

#include "library.hpp"

int main()
{
	assert(library_v1::test(1) == 1);

//  -------------------------------------------------------------------------

	auto path = "liblibrary_v2.so";

	assert(boost::dll::import_symbol < int(int) > (path, "test_v1")(1) == 1);
	assert(boost::dll::import_alias  < int(int) > (path, "test_v2")(1) == 1);
}