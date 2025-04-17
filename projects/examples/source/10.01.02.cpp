/////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iterator>
#include <type_traits>
#include <vector>

/////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------------

	vector.erase(vector.insert(std::next(std::begin(vector), 0), 1));

	vector.erase(vector.insert(std::next(std::begin(vector), 2), 1));

	vector.erase(vector.insert(std::next(std::begin(vector), 5), 1));

//  -----------------------------------------------------------------

	assert(vector.at(0) == 1);

//  -----------------------------------------------------------------

    static_assert
	(
		std::is_same_v 
		< 
			std::vector < int > ::iterator::iterator_category,
			
			std::random_access_iterator_tag 
		> 
	);
}

/////////////////////////////////////////////////////////////////////