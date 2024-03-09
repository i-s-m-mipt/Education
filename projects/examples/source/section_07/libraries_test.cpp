#include <exception>
#include <iostream>
#include <string>

#include "library.hpp"

#include <boost/dll.hpp>

using namespace std::literals;

int main()
{
	std::cout << library_v1::f(42) << std::endl;

	const auto path = "../../../libraries/library_v2/liblibrary_v2.so"s;

	try 
	{
		auto f = boost::dll::import_symbol < int(int) > (path, "f"); // note: not import

		std::cout << f(42) << std::endl;

		auto variable = boost::dll::import_symbol < int > (path, "global_variable");

		std::cout << *variable << std::endl;

		auto run = boost::dll::import_alias < int(int) > (path, "run");

		std::cout << run(42) << std::endl;
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << '\n';
	}

	return 0;
}