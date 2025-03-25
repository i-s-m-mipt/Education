#include <cstddef>
#include <cstdint>
#include <type_traits>

//////////////////////////////////////////////////////////////////

int main()
{
	using alias_1 = int;

//  --------------------------------------------------------------

// 	typedef int alias_2; // bad

//  --------------------------------------------------------------

	alias_1 x = 1;

//  --------------------------------------------------------------

	static_assert(std::is_same_v < decltype(x), int > );

//  --------------------------------------------------------------

	static_assert(std::is_same_v < std::size_t, unsigned long > );

//  --------------------------------------------------------------

	static_assert(sizeof(std::int16_t) == 2);

	static_assert(sizeof(std::int32_t) == 4);

	static_assert(sizeof(std::int64_t) == 8);
}