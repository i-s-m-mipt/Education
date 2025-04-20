//////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <ranges>
#include <type_traits>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////

auto   test_v1() {        std::vector < int > vector = { 1, 2, 3, 4, 5 }; return vector; }

auto & test_v2() { static std::vector < int > vector = { 1, 2, 3, 4, 5 }; return vector; }

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto iterator_1 = std::ranges::max_element(test_v1());

	auto iterator_2 = std::ranges::max_element(test_v2());

//  -----------------------------------------------------------------------------------

	static_assert(std::is_same_v < decltype(iterator_1), std::ranges::dangling > == 1);

	static_assert(std::is_same_v < decltype(iterator_2), std::ranges::dangling > == 0);

//  -----------------------------------------------------------------------------------

//	assert(*iterator_1 == 5); // error

	assert(*iterator_2 == 5);
}

//////////////////////////////////////////////////////////////////////////////////////////