//////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////

class Entity 
{
public :

// ~Entity() = default; // error

//  ----------------------------------

	virtual ~Entity() = default;

//  ----------------------------------

	virtual void test() const
	{ 
		std::cout << "Entity::test\n";
	}
};

//////////////////////////////////////////////////////////

class Client : public Entity
{
public :

	void test() const override final
	{ 
		std::cout << "Client::test\n";
	}
};

//////////////////////////////////////////////////////////

class Server final : public Entity {};

//////////////////////////////////////////////////////////

class Router : private Entity {};

//////////////////////////////////////////////////////////

int main()
{
//  std::vector < Client > clients; // bad

//  std::vector < Server > servers; // bad

//  ------------------------------------------------------

    Client client;

	Server server;

	Router router;

//  ------------------------------------------------------

	[[maybe_unused]] Entity * entity_1 = &client;

	[[maybe_unused]] Entity * entity_2 = &server;
	
	[[maybe_unused]] Entity & entity_3 =  client;

//	[[maybe_unused]] Entity   entity_4 =  server; // error

//	[[maybe_unused]] Entity * entity_5 = &router; // error

//  ------------------------------------------------------

	std::vector < Entity * > entities;

//  ------------------------------------------------------

    entities.push_back(new Client);

	entities.push_back(new Server);

//  ------------------------------------------------------

    for (auto entity : entities)
    {
        entity->test(); // support : compiler-explorer.com
    }

//  ------------------------------------------------------

    for (auto entity : entities)
    {
        delete entity;
    }
}

//////////////////////////////////////////////////////////