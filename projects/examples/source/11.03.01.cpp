#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

//////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector_1 = { 1, 2, 3, 4, 5 };

	std::vector < int > vector_2;

//  ----------------------------------------------------------

	std::ranges::copy(vector_1, std::back_inserter(vector_2));

//  ----------------------------------------------------------

	assert(vector_1 == vector_2);
}