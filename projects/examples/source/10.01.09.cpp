#include <cassert>
#include <iterator>
#include <list>
#include <type_traits>

/////////////////////////////////////////////////////////////////////

int main()
{
    std::list < int > list = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------------

	list.push_back (1);

    list. pop_back ( );

//  -----------------------------------------------------------------
		
	list.push_front(1);

    list. pop_front( );

//  -----------------------------------------------------------------

	list.insert(std::next(std::begin(list), std::size(list) / 2), 1);

	list.erase (std::next(std::begin(list), std::size(list) / 2));

//  -----------------------------------------------------------------

	static_assert
	(
		std::is_same_v 
		< 
			std::list < int > ::iterator::iterator_category, 
			
			std::bidirectional_iterator_tag 
		> 
	);
}