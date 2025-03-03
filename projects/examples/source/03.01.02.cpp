#include <cassert>

////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data_1 = 0, data_2 = 0;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity(1, 1), * p_entity = &entity, & r_entity = entity;

//  ----------------------------------------------------------------------------

	assert(entity.data_1 == 1 && p_entity->data_1 == 1 && r_entity.data_1 == 1);

	assert(entity.data_2 == 1 && p_entity->data_2 == 1 && r_entity.data_2 == 1);

//  ----------------------------------------------------------------------------

//	assert((*p_entity).data_1 == 1); // bad

//  ----------------------------------------------------------------------------

	assert
	(
		static_cast < void * > (&entity) ==

		static_cast < void * > (&entity.data_1)
	);
}