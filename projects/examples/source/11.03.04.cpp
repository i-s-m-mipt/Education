#include <algorithm>
#include <cassert>
#include <iterator>
#include <random>
#include <vector>

/////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };

	std::default_random_engine engine;

//  -----------------------------------------------------------------

	std::shuffle(std::begin(vector), std::end(vector), engine);

//  -----------------------------------------------------------------

	auto iterator = std::next(std::begin(vector), 2);

//  -----------------------------------------------------------------

	std::nth_element(std::begin(vector), iterator, std::end(vector));

//  -----------------------------------------------------------------

    assert(vector[0] < *iterator && vector[1] < *iterator);

    assert(vector[3] > *iterator && vector[4] > *iterator);
}