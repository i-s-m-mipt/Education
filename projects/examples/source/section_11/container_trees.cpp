#include <cassert>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <type_traits>

int main()
{
	std::set < int > set = { 1, 4, 2, 5, 3 }; // note: O(log(N)) complexity mainly

	using category_t = typename decltype(set)::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::bidirectional_iterator_tag > );

	for (auto element : set) std::cout << element << ' '; // note: outputs 0 1 2 3 4

	std::cout << std::endl;

	set.insert(std::cbegin(set), 0); // good: O(1) complexity (amortized) at best

	assert(!set.insert(1).second); // note: insert differs for std::multiset

	assert( set.erase(3) == 1); // note: erases all elements with provided key
	assert( set.count(3) == 0); // note: counts all elements with provided key

	assert(!set.contains(3)); // note: better than set.find(3) == std::end(set)

	assert(*set.lower_bound(3) == 4 && *set.upper_bound(3) == 4); // note: 0 1 2 4 5
	assert(*set.lower_bound(4) == 4 && *set.upper_bound(4) == 5); // note: 0 1 2 4 5

	auto node = set.extract(1); node.value() = 3; set.insert(std::move(node));

	std::map < std::string, int > map; // note: O(log(N)) complexity mainly

	map.insert(std::make_pair("hello", 41)); // good: prefer std::make_pair function

	map["world"] = map.at("hello"); map.erase("hello"); // note: way to change the key

	assert(!map.    emplace("world", 42).second); // note:    additional actions
	assert(!map.try_emplace("world", 42).second); // good: no additional actions

	assert(!map.insert_or_assign("world", 42).second); // note: changes value here

	assert(std::size(map) == 1 && map.at("world") == 42);

	return 0;
}