///////////////////////////////////////////////////////////////////////

// chapter : Functions

///////////////////////////////////////////////////////////////////////

// content : Character Types and Literals
//
// content : Type char
//
// content : American Standard Code for Information Interchange (ASCII)
//
// content : Encoding ASCII 7-bit
//
// content : Escape Sequences
//
// content : Type Trait std::is_signed
//
// content : Runtime Assertions
//
// content : Macro assert
//
// content : Helper std::numeric_limits
//
// content : Portability Problem

///////////////////////////////////////////////////////////////////////

// support : https://en.wikipedia.org/wiki/ASCII

///////////////////////////////////////////////////////////////////////

#include <cassert>
#include <limits>
#include <type_traits>

///////////////////////////////////////////////////////////////////////

int main()
{
	[[maybe_unused]] char x = 'a', y = '\0', z = '\n';

//  -----------------------------------------------------

	static_assert(sizeof(char) == 1);

//  -----------------------------------------------------

	static_assert(std::is_signed_v < char > );

//  -----------------------------------------------------

	assert(std::numeric_limits < char > ::max() == +127);

	assert(std::numeric_limits < char > ::min() == -128);
}

///////////////////////////////////////////////////////////////////////