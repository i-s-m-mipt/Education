////////////////////////////////////////////

// chapter : Basics of Programming

////////////////////////////////////////////

// section : Operators and Expressions

////////////////////////////////////////////

// content : Unspecified Behavior
//
// content : Evaluation Order
//
// content : Operator Associativity
//
// content : Operator ,

////////////////////////////////////////////

#include <cassert>

////////////////////////////////////////////

int main()
{
    auto x = (1 + 2) / (1 + 2);

//  ----------------------------------------

//	assert(x + ++x == 3); // error

//  ----------------------------------------

	[[maybe_unused]] auto y = x = 1 + 2 + 3;

//  ----------------------------------------

//	assert((++x, ++y) == 7); // bad
}

////////////////////////////////////////////