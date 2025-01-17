#include <algorithm>
#include <cassert>
#include <deque>
#include <iterator>
#include <list>
#include <set>
#include <vector>

/////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		std::deque < int > deque;

		std::ranges::copy(vector, std::front_inserter(deque));

		assert(std::size(deque) == std::size(vector));
	}

//  -----------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		std::list < int > list;

		std::ranges::copy(vector, std::back_inserter(list));

		assert(std::size(list) == std::size(vector));
	}

//  -----------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		std::set < int > set;

		std::ranges::copy(vector, std::inserter(set, std::end(set)));

		assert(std::size(set) == std::size(vector));
	}
}