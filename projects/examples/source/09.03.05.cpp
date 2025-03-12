#include <string>

/////////////////////////////////////

union Entity
{
	Entity() : data_1() {}

   ~Entity() {}

//  ---------------------------

	std::string data_1, data_2;
};

/////////////////////////////////////

int main()
{
    Entity entity;

//  ---------------------------------

	entity.data_1 = "aaaaa";

	entity.data_1.~basic_string();

//  ---------------------------------

	new (&entity.data_2) std::string;

//  ---------------------------------

	entity.data_2 = "aaaaa";

	entity.data_2.~basic_string();
}