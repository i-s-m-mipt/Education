#include <iostream>

////////////////////////////////////////////

class Entity_v1 
{ 
public:

	virtual ~Entity_v1() = default; 
};

class Client_v1 : public Entity_v1 {};

////////////////////////////////////////////

class Entity_v2 
{
public:

	virtual ~Entity_v2() = default;

//  -------------------------------------

	virtual Entity_v1 * test() const
	{ 
		std::cout << "Entity_v2::test\n";

		return new Entity_v1(); 
	}
};

////////////////////////////////////////////

class Client_v2 : public Entity_v2
{
public:

	Client_v1 * test() const override 
	{ 
		std::cout << "Client_v2::test\n";

		return new Client_v1(); 
	}
};

////////////////////////////////////////////

int main()
{
	Entity_v2 * entity_v2 = new Client_v2();

	delete entity_v2->test();

	delete entity_v2;
}