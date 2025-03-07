#include <iostream>
#include <string>

#include "08.02.08.hpp"

///////////////////////////////////////////////////////////////////////

int main()
{
    Python python;

//  -------------------------------------------------------------------

    try
	{
		auto statement = "from 08.02.09 import factorial";

		boost::python::exec(statement, python.local(), python.local());

//      ---------------------------------------------------------------

		auto object = python.local()["factorial"](100);
			
		auto x = boost::python::extract < std::string > (object)();

//      ---------------------------------------------------------------

        std::cout << "main : x = " << x << '\n';
	}
	catch (const boost::python::error_already_set &)
	{
		std::cerr << "main : " << Python::exception() << '\n';
	}
}