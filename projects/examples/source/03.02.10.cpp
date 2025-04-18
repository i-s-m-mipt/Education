///////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////

class Entity 
{
public :

	Entity()
	{
		std::cout << "Entity::Entity\n";

	//  --------------------------------

	//	test_v1(); // bad
	}

//  -----------------------------------------

// ~Entity() = default; // error

//  -----------------------------------------

	virtual ~Entity() = default;

//  -----------------------------------------

	virtual void test_v1() const
	{ 
		std::cout << "Entity::test_v1\n";
	}

//  -----------------------------------------

	virtual void test_v2() const = 0;

//  -----------------------------------------

//	virtual void test_v3() const = 0 // error
//	{
//		std::cout << "Entity::test_v3\n";
//	}
};

///////////////////////////////////////////////////////////

void Entity::test_v2() const
{ 
	std::cout << "Entity::test_v2\n";
}

///////////////////////////////////////////////////////////

class Client : public Entity
{
public :

	void test_v1() const override final 
	{ 
		std::cout << "Client::test_v1\n";
	}

//  -------------------------------------

	void test_v2() const override 
	{ 
		std::cout << "Client::test_v2\n";

	//  ---------------------------------
		
		Entity::test_v2();
	}
};

///////////////////////////////////////////////////////////

class Server final : public Entity 
{
public :

	void test_v2() const override
	{ 
		std::cout << "Server::test_v2\n";

	//  ---------------------------------

		Entity::test_v2();
	}
};

///////////////////////////////////////////////////////////

class Router : private Entity 
{
public :

	void test_v2() const override 
	{ 
		std::cout << "Router::test_v2\n";
	}
};

///////////////////////////////////////////////////////////

int main()
{
//  std::vector < Client > clients; // bad

//  std::vector < Server > servers; // bad

//  -------------------------------------------------------

    Client client;

	Router router;

//  -------------------------------------------------------

	[[maybe_unused]] Entity * entity_1 = &client;
	
	[[maybe_unused]] Entity & entity_2 =  client;

//	[[maybe_unused]] Entity   entity_3 =  client; // error

//	[[maybe_unused]] Entity * entity_4 = &router; // error

//  -------------------------------------------------------

    entity_1->test_v1(); // support : compiler-explorer.com

    entity_1->test_v2();

//  -------------------------------------------------------

	std::vector < Entity * > entities;
}

///////////////////////////////////////////////////////////