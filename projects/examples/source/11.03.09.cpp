#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

/////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector_1 = { 1, 2, 3, 4, 5 };

	std::vector < int > vector_2;

	std::vector < int > vector_3;

//  ---------------------------------------------------------------------

	auto lambda = [](auto x){ return x > 0; };

//  ---------------------------------------------------------------------

	std::ranges::copy   (vector_1, std::back_inserter(vector_2));

	std::ranges::copy_if(vector_1, std::back_inserter(vector_3), lambda);

//  ---------------------------------------------------------------------

	assert(vector_2 == vector_1);

	assert(vector_3 == vector_1);
}