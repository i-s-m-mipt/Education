///////////////////////////////////////////////

// chapter : Basics of Programming

///////////////////////////////////////////////

// section : Operators and Expressions

///////////////////////////////////////////////

// content : Operator / 
//
// content : Comparing Floating-Point Numbers
//
// content : Function std::abs
//
// content : Operator %

///////////////////////////////////////////////

#include <cassert>
#include <cmath>

///////////////////////////////////////////////

int main()
{
    auto x = 1, y = 2;

//  -------------------------------------------

	assert(std::abs(1.0 * x / y - 0.5) < 1e-6);

//  -------------------------------------------

	assert(+x % +y == +1);

	assert(+x % -y == +1);

	assert(-x % +y == -1);

	assert(-x % -y == -1);
}

///////////////////////////////////////////////