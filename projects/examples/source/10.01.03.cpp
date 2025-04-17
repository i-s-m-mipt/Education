///////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iterator>
#include <vector>

///////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector_1 = { 1, 2, 3, 4, 5 };

	std::vector < int > vector_2(std::begin(vector_1), std::end(vector_1));

	std::vector < int > vector_3
	(
		std::make_move_iterator(std::begin(vector_2)),
		
		std::make_move_iterator(std::end  (vector_2))
	);

//  -----------------------------------------------------------------------

	assert(std::size(vector_2) == 5);

	assert(std::size(vector_3) == 5);
}

///////////////////////////////////////////////////////////////////////////