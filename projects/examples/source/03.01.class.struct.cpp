#include <cassert>
#include <iterator>
#include <string>
#include <vector>

//  ================================================================================================

struct Entity 
{ 
	int data_1 = 0; 
	int data_2 = 0; 
};

//  ================================================================================================

[[nodiscard]] auto make_entity(int data_1, int data_2) 
{ 
	return Entity
	(
		data_1 < 0 ? 0 : data_1, 
		data_2 < 0 ? 0 : data_2
	); 
}

//  ================================================================================================

int main()
{
	[[maybe_unused]] Entity entity_1 {};
	
	[[maybe_unused]] Entity entity_2 { 2 };
	
	[[maybe_unused]] Entity entity_3 { 3, 3 };
	
	[[maybe_unused]] Entity entity_4 { .data_1 = 4 };

	[[maybe_unused]] Entity entity_5 { .data_1 = 5, .data_2 = 5 };

	[[maybe_unused]] Entity entity_6 { .data_2 = 6 };

//	[[maybe_unused]] Entity entity_7 { .data_2 = 7, .data_1 = 7 }; // error

//  ------------------------------------------------------------------------------------------------

	entity_1.data_1 = 1;

	auto p_entity_1 = &entity_1;

//	(*p_entity_1).data_1 = 1; // bad

	p_entity_1->data_1 = 1;

	auto & r_entity_1 = entity_1;

	r_entity_1.data_1 = 1;

//  ------------------------------------------------------------------------------------------------

	assert
	(
		static_cast < void * > (&entity_1       ) == 
		static_cast < void * > (&entity_1.data_1)
	);

//  ------------------------------------------------------------------------------------------------

	[[maybe_unused]] const Entity entity_8;

//	entity_8 = { 8, 8 }; // error

//  ------------------------------------------------------------------------------------------------

	std::vector < Entity > entities { { 1, 1 }, make_entity(2, 2), entity_3 };
}