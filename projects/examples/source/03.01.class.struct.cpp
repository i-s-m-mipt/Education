#include <cassert>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data_1 = 0, data_2 = 0; 
};

////////////////////////////////////////////////////////////////////////////////////////

auto make_entity(int data_1, int data_2) 
{ 
	return Entity
	(
		data_1 < 0 ? 0 : data_1, 
		
		data_2 < 0 ? 0 : data_2
	); 
}

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		[[maybe_unused]] Entity entity_1 {};
		
		[[maybe_unused]] Entity entity_2 { 2 };
		
		[[maybe_unused]] Entity entity_3 { 3, 3 };
		
		[[maybe_unused]] Entity entity_4 { .data_1 = 4 };

		[[maybe_unused]] Entity entity_5 { .data_1 = 5, .data_2 = 5 };

		[[maybe_unused]] Entity entity_6 { .data_2 = 6 };

//		[[maybe_unused]] Entity entity_7 { .data_2 = 7, .data_1 = 7 }; // error
	}
	
//  ------------------------------------------------------------------------------------

	{
		Entity entity(1, 1);

		assert(entity.data_1 == 1);

		auto p_entity = &entity;

//		assert((*p_entity).data_1 == 1); // bad

		assert(p_entity->data_1 == 1);

		auto & r_entity = entity;

		assert(r_entity.data_1 == 1);
	}

//  ------------------------------------------------------------------------------------

	{
		std::vector < Entity > entities = { { 1, 1 }, Entity(2, 2), make_entity(3, 3) };
	}
}