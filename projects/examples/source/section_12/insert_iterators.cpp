#include <algorithm>
#include <cassert>
#include <deque>
#include <iterator>
#include <list>
#include <set>
#include <vector>

int main()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::deque < int > deque; // note: std::deque has push_front member function

	std::ranges::copy(vector, std::front_inserter(deque));

	assert(std::size(deque) == std::size(vector));

	std::list < int > list; // note: std::list has push_back member function

	std::ranges::copy(vector, std::back_inserter(list));

	assert(std::size(list) == std::size(vector));

	std::set < int > set; // note: std::set has only insert member function

	std::ranges::copy(vector, std::inserter(set, std::begin(set)));

	assert(std::size(set) == std::size(vector));

	return 0;
}