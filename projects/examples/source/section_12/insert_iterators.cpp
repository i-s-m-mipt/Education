#include <algorithm>
#include <cassert>
#include <deque>
#include <iterator>
#include <list>
#include <set>
#include <utility>
#include <vector>

int main()
{
	const std::vector < int > vector = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::deque < int > deque; // note: std::deque has push_front member function

	std::ranges::copy(vector, std::front_inserter(deque)); // note: copy range via push_front

	assert(std::size(deque) == std::size(vector));

	std::list < int > list; // note: std::list has push_back member function

	std::ranges::copy(vector, std::back_inserter(list)); // note: copy range via push_back

	assert(std::size(list) == std::size(vector));

	std::set < int > set; // note: std::set has only insert member function

	std::ranges::copy(vector, std::inserter(set, std::end(set))); // note: copy range via insert

	assert(std::size(set) == std::size(vector));

	return 0;
}