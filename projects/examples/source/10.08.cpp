//////////////////////////////////////////////////////////////////

#include <cassert>
#include <deque>
#include <iterator>
#include <type_traits>

//////////////////////////////////////////////////////////////////

int main()
{
    std::deque < int > deque = { 1, 2, 3, 4, 5 };

//  --------------------------------------------------------------

    static_assert
	(
		std::is_same_v 
		< 
			decltype(deque)::iterator::iterator_category,
			
			std::random_access_iterator_tag 
		> 
	);

//  --------------------------------------------------------------

	deque.erase(deque.insert(std::next(std::begin(deque), 0), 1));

	deque.erase(deque.insert(std::next(std::begin(deque), 2), 1));

	deque.erase(deque.insert(std::next(std::begin(deque), 5), 1));

//  --------------------------------------------------------------

    assert(deque.at(0) == 1);
}

//////////////////////////////////////////////////////////////////