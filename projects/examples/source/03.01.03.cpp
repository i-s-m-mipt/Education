#include <algorithm>
#include <cassert>
#include <vector>

///////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data_1 = 0, data_2 = 0;
};

///////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < Entity > entities(5);

//  -----------------------------------------------------------------------

	for (auto i = 0uz; i < std::size(entities); ++i)
	{
		entities[i].data_1 = i + 1;

		entities[i].data_2 = i + 1;
	}

//  -----------------------------------------------------------------------

	assert(std::ranges::is_sorted(entities, std::less(), &Entity::data_1));

	assert(std::ranges::is_sorted(entities, std::less(), &Entity::data_2));
}