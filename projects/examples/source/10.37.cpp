/////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/RedBlack.html

/////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iterator>
#include <set>
#include <type_traits>
#include <utility>

/////////////////////////////////////////////////////////////////

int main()
{
	std::set < int > set = { 5, 4, 3, 2, 1 };

//  ----------------------------------------------------------
	
    static_assert
    (
        std::is_same_v 
        < 
            decltype(set)::iterator::iterator_category, 
                
            std::bidirectional_iterator_tag 
        > 
    );

//  ----------------------------------------------------------
		
	assert(std::ranges::is_sorted(set));

//  ----------------------------------------------------------

	assert(set.contains(1) == (set.find(1) != std::end(set)));

//  ----------------------------------------------------------

	assert(set.erase(1) == 1 && set.insert(1).second);

//  ----------------------------------------------------------

	auto begin = std::begin(set);

//  ----------------------------------------------------------

	assert(set.lower_bound(1) == std::next(begin, 0));
		
	assert(set.upper_bound(1) == std::next(begin, 1));

//  ----------------------------------------------------------

//	*begin = 2; // error

//  ----------------------------------------------------------

	auto node = set.extract(1);

//  ----------------------------------------------------------
		
	node.value() = 2;

//  ----------------------------------------------------------
		
	set.insert(std::move(node));
}

/////////////////////////////////////////////////////////////////