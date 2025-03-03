#include <iostream>
#include <utility>

/////////////////////////////////////////////////////////

struct Entity {};

/////////////////////////////////////////////////////////

void test(      Entity & ) { std::cout << "test (1)\n"; }

void test(const Entity & ) { std::cout << "test (2)\n"; }

void test(      Entity &&) { std::cout << "test (3)\n"; }

void test(const Entity &&) { std::cout << "test (4)\n"; }

/////////////////////////////////////////////////////////

int main()
{
	Entity entity_1;

	test(entity_1);

//  --------------------------

	const Entity entity_2;
		
	test(entity_2);

//  --------------------------

	Entity entity_3;

	test(std::move(entity_3));

//  --------------------------

	test(Entity());
}