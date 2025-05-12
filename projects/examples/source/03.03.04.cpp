/////////////////////////////////////////////////////////////

#include <iostream>
#include <utility>

/////////////////////////////////////////////////////////////

struct Entity {};

/////////////////////////////////////////////////////////////

void handle(Entity       & ) { std::cout << "handle (1)\n"; }

void handle(Entity const & ) { std::cout << "handle (2)\n"; }

void handle(Entity       &&) { std::cout << "handle (3)\n"; }

void handle(Entity const &&) { std::cout << "handle (4)\n"; }

/////////////////////////////////////////////////////////////

int main()
{
	Entity       entity_1;

	Entity const entity_2;

//  -----------------------------------

	handle(entity_1);

	handle(entity_2);

//  -----------------------------------

	handle(std::move(entity_1));

//	handle(std::move(entity_2)); // bad

//  -----------------------------------

	handle(Entity());
}

/////////////////////////////////////////////////////////////