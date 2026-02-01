////////////////////////////////////////

// chapter : Basics of Programming

////////////////////////////////////////

// section : Operators and Expressions

////////////////////////////////////////

// content : Unary and Binary Operators
//
// content : Logical Operators
//
// content : Alternative Representations
//
// content : Operator Precedence
//
// content : Short-Circuit Evaluations
//
// content : De Morgan's Rules
//
// content : Expressions and Statements

////////////////////////////////////////

#include <cassert>

////////////////////////////////////////

int main()
{
	auto x = false, y = true;

//  ------------------------------

	assert(!x == 1);

	assert(!y == 0);

//  ------------------------------

	assert(!x == not x);

//  ------------------------------

	assert((x && x) == 0);

	assert((x && y) == 0);

	assert((y && x) == 0);

	assert((y && y) == 1);

//  ------------------------------

	assert((x && y) == (x and y));

//  ------------------------------

	assert((x || x) == 0);
	
	assert((x || y) == 1);

	assert((y || x) == 1);

	assert((y || y) == 1);

//  ------------------------------

	assert((x || y) == (x or  y));
}

////////////////////////////////////////