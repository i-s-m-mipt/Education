///////////////////////////////////////////

// chapter : Memory Management

///////////////////////////////////////////

// section : Dynamic Memory

///////////////////////////////////////////

// content : Non-Trivial Union Data Members

///////////////////////////////////////////

#include <memory>
#include <string>

///////////////////////////////////////////

union Entity
{
	Entity() : string_1() {}

//  ------------------------

   ~Entity() {}

//  ------------------------

	std::string string_1;
	
	std::string string_2;
};

///////////////////////////////////////////

int main()
{
    Entity entity;

//  -----------------------------------

	entity.string_1 = "aaaaa";

//  -----------------------------------

	std::destroy_at(&entity.string_1);

//  -----------------------------------

	new (&entity.string_2) std::string;

//  -----------------------------------

	entity.string_2 = "aaaaa";

//  -----------------------------------

	std::destroy_at(&entity.string_2);
}

///////////////////////////////////////////