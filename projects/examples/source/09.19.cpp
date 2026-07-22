/////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

/////////////////////////////////////////////////////////////////////////////////

// content : Memory Access Granularity
//
// content : Data Alignment
//
// content : Attribute [[packed]]
//
// content : Operator alignof
//
// content : Type Trait std::has_unique_object_representations
//
// content : Compressed Pairs
//
// content : Library Boost.Utility

/////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <type_traits>
#include <utility>

/////////////////////////////////////////////////////////////////////////////////

#include <boost/compressed_pair.hpp>

/////////////////////////////////////////////////////////////////////////////////

struct Entity_v1 { std::int16_t x = 0; std::int64_t y = 0; std::int32_t z = 0; };

struct Entity_v2 { std::int16_t x = 0; std::int32_t y = 0; std::int64_t z = 0; };

/////////////////////////////////////////////////////////////////////////////////

struct __attribute__((packed)) Entity_v3
{
	std::int16_t x = 0;

	std::int32_t y = 0;

	std::int64_t z = 0;
};

/////////////////////////////////////////////////////////////////////////////////

struct Entity_v4 {};

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(sizeof(Entity_v1) == 24 && alignof(Entity_v1) == 8);

	static_assert(sizeof(Entity_v2) == 16 && alignof(Entity_v2) == 8);

	static_assert(sizeof(Entity_v3) == 14 && alignof(Entity_v3) == 1);

//  ---------------------------------------------------------------------------

	static_assert(std::has_unique_object_representations_v < Entity_v1 > == 0);

	static_assert(std::has_unique_object_representations_v < Entity_v2 > == 0);

	static_assert(std::has_unique_object_representations_v < Entity_v3 > == 1);

//  ---------------------------------------------------------------------------

	static_assert(sizeof(Entity_v4) == 1);

//  ---------------------------------------------------------------------------

	static_assert(sizeof(std::pair < Entity_v4, int > ) == 8);

//  ---------------------------------------------------------------------------

	static_assert(sizeof(boost::compressed_pair < Entity_v4, int > ) == 4);
}

/////////////////////////////////////////////////////////////////////////////////