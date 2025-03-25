#include <iostream>
#include <string>

#include "08.02.09.hpp"

///////////////////////////////////////////////////////////////////

int main()
{
    Python python;

//  ---------------------------------------------------------------

    try
	{
		auto statement = "from 08.02.11 import factorial";

		const auto & local = python.local();

	//  -----------------------------------------------------------

		boost::python::exec(statement, local, local);

		auto object = local["factorial"](100);
			
		auto x = boost::python::extract < std::string > (object)();

	//  -----------------------------------------------------------

        std::cout << "main : x = " << x << '\n';
	}
	catch (const boost::python::error_already_set &)
	{
		std::cerr << "main : " << Python::exception() << '\n';
	}
}