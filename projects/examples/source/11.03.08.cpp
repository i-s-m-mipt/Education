#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int x = 0;
};

////////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < Entity > entities = { { 1 }, { 2 }, { 3 }, { 4 }, { 5 } };

//  ------------------------------------------------------------------------

	std::ranges::sort(entities, std::greater(), &Entity::x);

//  ------------------------------------------------------------------------

	assert(std::ranges::is_sorted(entities, std::greater(), &Entity::x));
}