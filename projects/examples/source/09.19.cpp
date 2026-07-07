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

////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////

struct Entity_v1 { std::int8_t x = 0; std::int32_t y = 0; std::int16_t z = 0; };

struct Entity_v2 { std::int8_t x = 0; std::int16_t y = 0; std::int32_t z = 0; };

////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(sizeof(Entity_v1) == 12 && alignof(Entity_v1) == 4);

	static_assert(sizeof(Entity_v2) ==  8 && alignof(Entity_v2) == 4);

//  ------------------------------------------------------------------------

	static_assert(!std::has_unique_object_representations_v < Entity_v1 > );

	static_assert(!std::has_unique_object_representations_v < Entity_v2 > );
}

////////////////////////////////////////////////////////////////////////////////