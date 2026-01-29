//////////////////////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

//////////////////////////////////////////////////////////////////////

// section : User-Defined Data Types

//////////////////////////////////////////////////////////////////////

// content : Operators . and ->
//
// content : Pointers to Data Members

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
    Entity entity_1(1, 1), * entity_2 = &entity_1;

//  ------------------------------------------------------------------

	assert(entity_1.x == 1 && (*entity_2).x == entity_2->x);

	assert(entity_1.y == 1 && (*entity_2).y == entity_2->y);

//  ------------------------------------------------------------------

	assert
	(
		static_cast < void * > (&entity_1  ) ==

		static_cast < void * > (&entity_1.x)
	);

//  ------------------------------------------------------------------

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