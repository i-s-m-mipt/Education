#include <cassert>
#include <map>
#include <set>

int main()
{
	std::set < int > set;

	set.insert(1);
	set.insert(2);
	set.insert(4);
	set.insert(5);

	assert(!set.insert(1).second); // note: differs for std::multiset

	assert(!set.erase(3));

	assert(!set.contains(3)); // note: better than set.find(3) == std::end(set)

	assert(*set.lower_bound(3)        == 4);
	assert(*set.upper_bound(3)        == 4);
	assert(*set.equal_range(3).first  == 4);
	assert(*set.equal_range(3).second == 4);

	assert(*set.lower_bound(4)        == 4);
	assert(*set.upper_bound(4)        == 5);
	assert(*set.equal_range(4).first  == 4);
	assert(*set.equal_range(4).second == 5);

	auto node = set.extract(1); node.value() = 3; set.insert(std::move(node));

	assert(!set.contains(1));
	assert( set.contains(3));

	return 0;
}