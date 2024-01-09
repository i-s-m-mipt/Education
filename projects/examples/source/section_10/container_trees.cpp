#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <type_traits>

int main()
{
	std::set < int > set({1, 5, 3, 4, 2}); // note: O(log(N)) complexity for operations

	using category_t = typename decltype(set)::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::bidirectional_iterator_tag > );

	for (auto iterator = std::cbegin(set); iterator != std::cend(set); ++iterator)
	{
		std::cout << *iterator << ' ';
	}

	set.insert(std::begin(set), 0); // good: O(1) complexity (amortized) at best

	assert(!set.insert(1).second); // note: insert differs for std::multiset

	assert( set.erase(3) == 1); // note: erases all elements with provided key
	assert( set.count(3) == 0); // note: counts all elements with provided key

	assert(!set.contains(3)); // note: better than set.find(3) == std::end(set)

	assert(*set.lower_bound(3) == 4 && *set.upper_bound(3) == 4); // 0 1 2 4 5
	assert(*set.lower_bound(4) == 4 && *set.upper_bound(4) == 5); // 0 1 2 4 5

	auto node = set.extract(1); node.value() = 3; set.insert(std::move(node));

	std::map < std::string, int > map; // note: O(log(N)) complexity for operations

	map.insert(std::make_pair("hello", 42)); // good: prefer std::make_pair function

	map["world"] = map.at("hello"); map.erase("hello"); // note: way to change the key

	return 0;
}