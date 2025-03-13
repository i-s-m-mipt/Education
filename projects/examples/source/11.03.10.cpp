#include <algorithm>
#include <cassert>
#include <ranges>
#include <type_traits>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto lambda = [](){ return std::vector < int > ({ 1, 2, 3, 4, 5 }); };

//  -----------------------------------------------------------------------------

	auto iterator = std::ranges::max_element(lambda());

//  -----------------------------------------------------------------------------
		
	static_assert(std::is_same_v < decltype(iterator), std::ranges::dangling > );

//  -----------------------------------------------------------------------------

//	assert(*terator == 5); // error
}