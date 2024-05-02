#include <exception>
#include <iostream>
#include <string>

#include <boost/dll.hpp>

#include "library.hpp"

int main()
{
	std::cout << library_v1::f(42) << std::endl;

	const std::string path = "liblibrary_v2.so";

//  ================================================================================================

	const auto f = boost::dll::import_symbol < int(int) > (path, "f"); // note: not import since C++20

	std::cout << f(42) << std::endl;

//  ================================================================================================

	const auto variable = boost::dll::import_symbol < int > (path, "global_variable"); // note: pointer

	std::cout << *variable << std::endl;

//  ================================================================================================

	const auto run = boost::dll::import_alias < int(int) > (path, "run");

	std::cout << run(42) << std::endl;

	return 0;
}