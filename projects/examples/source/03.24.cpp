///////////////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

///////////////////////////////////////////////////////////////

// section : Dynamic Polymorphism

///////////////////////////////////////////////////////////////

// content : Wrapper std::any
//
// content : Function std::any_cast
//
// content : Operator ""s
//
// content : Namespace std::literals

///////////////////////////////////////////////////////////////

#include <any>
#include <cassert>
#include <cmath>
#include <string>

///////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////

int main()
{
	std::any any;

//  -----------------------------------------------------------

	if (any = 1; any.type() == typeid(int))
	{
		assert(std::any_cast < int > (any) == 1);
	}

//  -----------------------------------------------------------

	if (any = 2.0; any.type() == typeid(double))
	{
		assert(equal(std::any_cast < double > (any), 2.0));
	}

//  -----------------------------------------------------------

	if (any = "aaaaa"s; any.type() == typeid(std::string))
	{
		assert(std::any_cast < std::string > (any) == "aaaaa");
	}
}

///////////////////////////////////////////////////////////////