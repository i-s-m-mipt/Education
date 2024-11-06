#include <iostream>

//  ================================================================================================

struct Entity_v1 
{ 
	virtual ~Entity_v1() = default; 
};

struct Client_v1 : public Entity_v1 {};

//  ================================================================================================

struct Entity_v2 
{
	virtual ~Entity_v2() = default;

//  ------------------------------------------------------------------------------------------------

	[[nodiscard]] virtual Entity_v1 * test() const
	{ 
		std::clog << "Entity_v2::test\n";

		return new Entity_v1(); 
	}
};

//  ================================================================================================

struct Client_v2 : public Entity_v2
{
	[[nodiscard]] Client_v1 * test() const override 
	{ 
		std::clog << "Client_v2::test\n";

		return new Client_v1(); 
	}
};

//  ================================================================================================

int main()
{
	Entity_v2 * entity_v2 = new Client_v2();

	delete entity_v2->test();

	delete entity_v2;
}