#include <cstddef>
#include <cstdint>
#include <type_traits>

//////////////////////////////////////////////////

int main()
{
	using alias = int;

	static_assert(std::is_same_v < alias, int > );

	[[maybe_unused]] alias x = 1;

//  ----------------------------------------------

	[[maybe_unused]] std::size_t size = 5;

//  ----------------------------------------------

// 	typedef int alias; // bad

//  ----------------------------------------------

	static_assert(sizeof(std::int16_t) == 2);

	static_assert(sizeof(std::int32_t) == 4);

	static_assert(sizeof(std::int64_t) == 8);
}