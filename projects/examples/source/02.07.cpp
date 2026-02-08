//////////////////////////////////////////////////////////////////////

// chapter : Basics of Programming

//////////////////////////////////////////////////////////////////////

// section : Types and Variables

//////////////////////////////////////////////////////////////////////

// content : Type Aliases
//
// content : Declarations using and typedef
//
// content : Type Alias std::size_t
//
// content : Type Aliases std::int16_t, std::int32_t and std::int64_t

//////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <cstdint>
#include <type_traits>

//////////////////////////////////////////////////////////////////////

int main()
{
	using alias_1 = int;

//  ------------------------------------------------------------------

	[[maybe_unused]] alias_1 x = 1;

//  ------------------------------------------------------------------

	static_assert(std::is_same_v < alias_1, int > );

//  ------------------------------------------------------------------

// 	typedef int alias_2; // bad

//  ------------------------------------------------------------------

	static_assert(std::is_same_v < std::size_t, unsigned long int > );

//  ------------------------------------------------------------------

	static_assert(sizeof(std::int16_t) == 2);

	static_assert(sizeof(std::int32_t) == 4);

	static_assert(sizeof(std::int64_t) == 8);
}

//////////////////////////////////////////////////////////////////////