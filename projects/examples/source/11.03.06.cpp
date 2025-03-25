#include <cassert>
#include <algorithm>
#include <iterator>
#include <vector>

///////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------

	auto iterator = std::begin(std::ranges::remove(vector, 1));

//  -----------------------------------------------------------

	assert(std::size(vector) == 5);

    assert(iterator == std::next(std::begin(vector), 4));

//  -----------------------------------------------------------

	vector.erase(iterator, std::end(vector));

//  -----------------------------------------------------------

	assert(vector == std::vector < int > ({ 2, 3, 4, 5 }));
}