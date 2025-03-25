#include <iostream>

///////////////////////////////////////////////////////////////

class Entity
{
public :

	void test() const &  { std::cout << "Entity::test (1)\n"; }

	void test() const && { std::cout << "Entity::test (2)\n"; }
};

///////////////////////////////////////////////////////////////

int main()
{
	Entity entity;
		
	entity.test();

//  ----------------
		
	Entity().test();
}