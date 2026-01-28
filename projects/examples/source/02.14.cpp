//////////////////////////////////////

// chapter : Basics of Programming

//////////////////////////////////////

// section : Operators and Expressions

//////////////////////////////////////

// content : Function std::swap
//
// content : Arithmetic Swap Algorithm

//////////////////////////////////////

#include <cassert>
#include <utility>

//////////////////////////////////////

int main()
{
    auto x = 1, y = 2;

//  -------------------------

	std::swap(x, y);

//  -------------------------

	assert(x == 2 && y == 1);

//  -------------------------

	x = x + y;

	y = x - y;

	x = x - y;

//  -------------------------

	assert(x == 1 && y == 2);
}

//////////////////////////////////////