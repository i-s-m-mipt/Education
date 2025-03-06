#include <cassert>
#include <ios>
#include <iostream>

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>

//////////////////////////////////////////////////////////////////////////////

int main()
{
	boost::logic::tribool x = false;

	boost::logic::tribool y = true;

	boost::logic::tribool z = boost::logic::indeterminate;

//  --------------------------------------------------------------------------

	assert((!x).value == 1);
	
	assert((!y).value == 0);
	
	assert((!z).value == 2);

//  --------------------------------------------------------------------------

	assert((x && x).value == 0 && (x && y).value == 0 && (x && z).value == 0);

	assert((y && x).value == 0 && (y && y).value == 1 && (y && z).value == 2);

	assert((z && x).value == 0 && (z && y).value == 2 && (z && z).value == 2);

//  --------------------------------------------------------------------------

	assert((x || x).value == 0 && (x || y).value == 1 && (x || z).value == 2);

	assert((y || x).value == 1 && (y || y).value == 1 && (y || z).value == 1);

	assert((z || x).value == 2 && (z || y).value == 1 && (z || z).value == 2);

//  --------------------------------------------------------------------------

	std::cout << "main : x = " << std::boolalpha << x << '\n';

	std::cout << "main : y = " << std::boolalpha << y << '\n';

	std::cout << "main : z = " << std::boolalpha << z << '\n';
}