///////////////////////////////////////////////////////////////

// chapter : Data Structures

///////////////////////////////////////////////////////////////

// section : Sequential Containers

///////////////////////////////////////////////////////////////

// content : Doubly Linked Lists
//
// content : Container std::list
//
// content : Bidirectional Iterators

///////////////////////////////////////////////////////////////

#include <cassert>
#include <iterator>
#include <list>
#include <type_traits>

///////////////////////////////////////////////////////////////

int main()
{
    std::list < int > list = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------

	static_assert
	(
		std::is_same_v
		<
			decltype(list)::iterator::iterator_category,

			std::bidirectional_iterator_tag 
		> 
	);

//  -----------------------------------------------------------

//  assert(list.at(0) == 1); // error

//  -----------------------------------------------------------

	list.erase(list.insert(std::next(std::begin(list), 0), 1));

	list.erase(list.insert(std::next(std::begin(list), 2), 1));

	list.erase(list.insert(std::next(std::begin(list), 5), 1));
}

///////////////////////////////////////////////////////////////