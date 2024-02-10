#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "python_wrapper.hpp"

using Python = solution::shared::Python;

int main()
{
    try
    {
        Python python;

        boost::python::exec("from python_script import factorial", 
            python.global(), python.global());
		
		std::cout << boost::python::extract < std::string > (
            python.global()["factorial"](100))() << std::endl;
    }
    catch ([[maybe_unused]] const boost::python::error_already_set & error)
	{
		std::cerr << Python::exception() << '\n';
	}
    catch (const std::exception & exception)
    {
        std::cerr << exception.what() << '\n';
    }
    
    return 0;
}