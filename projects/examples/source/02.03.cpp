///////////////////////////////////////////////////////////////////////////

// chapter : Basics of Programming

///////////////////////////////////////////////////////////////////////////

// section : Types and Variables

///////////////////////////////////////////////////////////////////////////

// content : Integral Types
//
// content : Integer Types and Literals
//
// content : Type int
//
// content : Type Modifiers short and long
//
// content : Literal Suffixes l and ll
//
// content : Hungarian Naming Convention
//
// content : Overflow Problem

///////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <limits>

///////////////////////////////////////////////////////////////////////////

int main()
{
	short int x1 = 1; int x2 = 2; long int x3 = 3l; long long int x4 = 4ll;

//  -----------------------------------------------------------------------

	static_assert(sizeof(x1) == 2);

	static_assert(sizeof(x2) == 4);

	static_assert(sizeof(x3) == 8);

	static_assert(sizeof(x4) == 8);

//  -----------------------------------------------------------------------

	assert(std::numeric_limits < int > ::max() == +2'147'483'647);
		
	assert(std::numeric_limits < int > ::min() == -2'147'483'648);
}

///////////////////////////////////////////////////////////////////////////