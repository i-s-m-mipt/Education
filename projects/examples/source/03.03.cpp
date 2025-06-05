//////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

//////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int x = 0, y = 0;
};

//////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < Entity > entities(5);

//  ------------------------------------------------------------------

	for (auto i = 0uz; i < std::size(entities); ++i)
	{
		entities[i].x = i + 1;

		entities[i].y = i + 1;
	}

//  ------------------------------------------------------------------

	assert(std::ranges::is_sorted(entities, std::less(), &Entity::x));

	assert(std::ranges::is_sorted(entities, std::less(), &Entity::y));
}

//////////////////////////////////////////////////////////////////////