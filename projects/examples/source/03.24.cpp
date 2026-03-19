//////////////////////////////////////////////////

// chapter : Object-Oriented Programming

//////////////////////////////////////////////////

// section : Rvalue References

//////////////////////////////////////////////////

// content : Extending Temporary Objects Lifetime

//////////////////////////////////////////////////

#include <cassert>

//////////////////////////////////////////////////

int main()
{
	auto x = 1.0;

//  ----------------------------------------------

//	[[maybe_unused]] int       &  y1 = x; // error

	[[maybe_unused]] int const &  y2 = x;

	[[maybe_unused]] int       && y3 = x;

	[[maybe_unused]] int const && y4 = x;

//  ----------------------------------------------

	assert(&y2 != &y3);

	assert(&y2 != &y4);

	assert(&y3 != &y4);
}

//////////////////////////////////////////////////