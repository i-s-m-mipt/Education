////////////////////////////////////////////////////////////

#include <cassert>

////////////////////////////////////////////////////////////

struct Entity
{ 
	int x = 0, y = 0;
};

////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1(1, 1), * entity_2 = &entity_1;

//  --------------------------------------------------------

	assert(entity_1.x == 1 && entity_2->x == (*entity_2).x);

	assert(entity_1.y == 1 && entity_2->y == (*entity_2).y);

//  --------------------------------------------------------

	assert
	(
		static_cast < void * > (&entity_1  ) ==

		static_cast < void * > (&entity_1.x)
	);
}

////////////////////////////////////////////////////////////