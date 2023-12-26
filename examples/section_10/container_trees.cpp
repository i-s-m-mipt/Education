#include <cassert>
#include <map>
#include <set>
#include <string>

int main()
{
	std::set < int > set; // note: O(log(N)) complexity for single operations

	set.insert(1); 
	set.insert(2);
	set.insert(4);
	set.insert(5);

	set.insert(std::begin(set), 0); // good: O(1) complexity (amortized)

	assert(!set.insert(1).second); // note: insert differs for std::multiset

	assert(!set.erase(3)); // note: removes all elements with provided key

	assert(!set.contains(3)); // note: better than set.find(3) == std::end(set)

	assert(*set.lower_bound(3) == 4 && *set.upper_bound(3) == 4);
	assert(*set.lower_bound(4) == 4 && *set.upper_bound(4) == 5);

	auto node = set.extract(1); node.value() = 3; set.insert(std::move(node));

	assert(!set.contains(1));
	assert( set.contains(3));

	std::map < std::string, int > map; // note: O(log(N)) complexity for single operations

	map.insert(std::make_pair("Jenssen", 26));

	map["Matthias"] = map.at("Jenssen");

	map.erase("Jenssen"); // note: the only way to change key

	return 0;
}