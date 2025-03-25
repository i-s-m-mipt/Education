#include <cassert>
#include <deque>
#include <iterator>
#include <tuple>
#include <type_traits>

/////////////////////////////////////////////////////////////

int main()
{
    std::deque < int > deque = { 1, 2, 3, 4, 5 };

//  ---------------------------------------------------------

	deque.push_back (1);

    deque. pop_back ( );

//  ---------------------------------------------------------
		
	deque.push_front(1);

    deque. pop_front( );

//  ---------------------------------------------------------

	deque.insert(std::next(std::begin(deque), 2), 1);

	deque.erase (std::next(std::begin(deque), 2)   );

//  ---------------------------------------------------------

    assert(deque.at(0) == 1);

//  ---------------------------------------------------------

    static_assert
	(
		std::is_same_v 
		< 
			std::deque < int > ::iterator::iterator_category,
			
			std::random_access_iterator_tag 
		> 
	);
}