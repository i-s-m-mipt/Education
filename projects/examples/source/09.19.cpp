////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

////////////////////////////////////////////////////////////////////////////////

// content : Memory Access Granularity
//
// content : Data Alignment
//
// content : Type Alias std::int8_t
//
// content : Operator alignof
//
// content : Type Trait std::has_unique_object_representations
//
// content : Compressed Pairs
//
// content : Library Boost.Utility

////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <type_traits>
#include <utility>

////////////////////////////////////////////////////////////////////////////////

#include <boost/compressed_pair.hpp>

////////////////////////////////////////////////////////////////////////////////

struct Entity_v1 { std::int8_t x = 0; std::int32_t y = 0; std::int16_t z = 0; };

struct Entity_v2 { std::int8_t x = 0; std::int16_t y = 0; std::int32_t z = 0; };

////////////////////////////////////////////////////////////////////////////////

struct Entity_v3 {};

////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(sizeof(Entity_v1) == 12 && alignof(Entity_v1) == 4);

	static_assert(sizeof(Entity_v2) ==  8 && alignof(Entity_v2) == 4);

//  ------------------------------------------------------------------------

	static_assert(!std::has_unique_object_representations_v < Entity_v1 > );

	static_assert(!std::has_unique_object_representations_v < Entity_v2 > );

//  ------------------------------------------------------------------------

	static_assert(sizeof(Entity_v3) == 1);

//  ------------------------------------------------------------------------

	static_assert(sizeof(std::pair < Entity_v3, int > ) == 8);

//  ------------------------------------------------------------------------

	static_assert(sizeof(boost::compressed_pair < Entity_v3, int > ) == 4);
}

////////////////////////////////////////////////////////////////////////////////