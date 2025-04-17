///////////////////////////////////////

#include <string>

///////////////////////////////////////

union Entity
{
	Entity() : string_1() {}

//  ------------------------

   ~Entity() {}

//  ------------------------

	std::string string_1;
	
	std::string string_2;
};

///////////////////////////////////////

int main()
{
    Entity entity;

//  -----------------------------------

	entity.string_1 = "aaaaa";

	entity.string_1.~basic_string();

//  -----------------------------------

	new (&entity.string_2) std::string;

//  -----------------------------------

	entity.string_2 = "aaaaa";

	entity.string_2.~basic_string();
}

///////////////////////////////////////