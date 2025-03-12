#include <algorithm>
#include <cassert>
#include <iterator>
#include <set>
#include <type_traits>
#include <utility>

////////////////////////////////////////////////////////////////////

int main()
{
	std::set < int > set = { 5, 4, 3, 2, 1 };

//  ------------------------------------------------------------
		
	assert(std::ranges::is_sorted(set));

//  ------------------------------------------------------------

	assert(set.find(1) != std::end(set) && set.contains(1));

//  ------------------------------------------------------------

	assert(set.insert(1).second == 0);

	std::ignore = set.erase(1);

	assert(set.insert(1).second == 1);

//  ------------------------------------------------------------

	assert(set.lower_bound(1) == std::begin(set));
		
	assert(set.upper_bound(1) == std::next(std::begin(set), 1));

//  ------------------------------------------------------------

//	*std::begin(set) = 2; // error

//  ------------------------------------------------------------

	auto node = set.extract(1);
		
	node.value() = 2;
		
	std::ignore = set.insert(std::move(node));

//  ------------------------------------------------------------
	
    static_assert
    (
        std::is_same_v 
        < 
            std::set < int > ::iterator::iterator_category, 
                
            std::bidirectional_iterator_tag 
        > 
    );
}