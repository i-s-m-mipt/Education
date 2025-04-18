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
		std::make_move_iterator(std::begin(vector_1)),
		
		std::make_move_iterator(std::end  (vector_1))
	);

//  -----------------------------------------------------------------------

	assert(vector_3 == vector_2 && std::size(vector_1) == 5);
}

///////////////////////////////////////////////////////////////////////////