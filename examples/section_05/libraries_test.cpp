#include <exception>
#include <iostream>
#include <string>

#include "library_v1/library.hpp"

#include <boost/dll.hpp>

using namespace std::literals;

int main()
{
	std::cout << library_v1::f(42) << std::endl;

	const auto path = "library_v2.dll"s;

	const auto name = "run"s;

	try 
	{
		auto f = boost::dll::import_symbol < int(int) > (path, "f");

		std::cout << f(42) << std::endl;

		auto variable = boost::dll::import_symbol < int > (path, "global_variable");

		std::cout << *variable << std::endl;

		auto g = boost::dll::import_alias < int(int) > (path, name);

		std::cout << g(42) << std::endl;
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << '\n';
	}

	return 0;
}