#include <exception>
#include <iostream>
#include <string>

#include "library_v1/library.hpp"

#include <boost/dll.hpp>

using namespace std::literals;

int main()
{
	std::cout << library_v1::f(42) << std::endl;

	const auto path_v2 = "library_v2.dll"s;

	const auto name_v2 = "run"s;

	try 
	{
		auto function_v2 = boost::dll::import_alias < int(int) > (path_v2, name_v2);

		std::cout << function_v2(42) << std::endl;
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << '\n';
	}

	return 0;
}