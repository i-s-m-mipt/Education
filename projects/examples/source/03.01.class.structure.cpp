#include <algorithm>
#include <cassert>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data_1 = 0, data_2 = 0;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		[[maybe_unused]] Entity entity_1, entity_2(2), entity_3(3, 3);
		
		[[maybe_unused]] Entity entity_4 { .data_1 = 4 };

		[[maybe_unused]] Entity entity_5 { .data_1 = 5, .data_2 = 5 };

		[[maybe_unused]] Entity entity_6 { .data_2 = 6 };

//		[[maybe_unused]] Entity entity_7 { .data_2 = 7, .data_1 = 7 }; // error
	}
	
//  --------------------------------------------------------------------------------

	{
		Entity entity(1, 1);

		auto p_entity = &entity; auto & r_entity = entity;

//		assert((*p_entity).data_1 == 1); // bad

		assert(entity.data_1 == 1 && p_entity->data_1 == 1 && r_entity.data_1 == 1);

		assert(entity.data_2 == 1 && p_entity->data_2 == 1 && r_entity.data_2 == 1);

		assert
		(
			static_cast < void * > (&entity) ==

			static_cast < void * > (&entity.data_1)
		);
	}

//  --------------------------------------------------------------------------------

	{
		std::vector < Entity > entities(5);

		for (auto i = 0uz; i < std::size(entities); ++i)
		{
			entities[i].data_1 = i + 1;

			entities[i].data_2 = i + 1;
		}

		assert(std::ranges::is_sorted(entities, std::less(), &Entity::data_1));

		assert(std::ranges::is_sorted(entities, std::less(), &Entity::data_2));
	}
}