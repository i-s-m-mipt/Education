/////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

/////////////////////////////////////////////////////////////

class Entity 
{
public :

// ~Entity() = default; // error

//  -------------------------------------

	virtual ~Entity()
	{
		std::cout << "Entity::~Entity\n";
	}

//  -------------------------------------

	virtual void test() const
	{ 
		std::cout << "Entity::test\n";
	}
};

/////////////////////////////////////////////////////////////

class Client : public Entity
{
public :

   ~Client() override
	{
		std::cout << "Client::~Client\n";
	}

//  -------------------------------------

	void test() const override final
	{ 
		std::cout << "Client::test\n";
	}
};

/////////////////////////////////////////////////////////////

class Server final : public Entity 
{
public:

   ~Server() override
	{
		std::cout << "Server::~Server\n";
	}
};

/////////////////////////////////////////////////////////////

class Router : private Entity {};

/////////////////////////////////////////////////////////////

int main()
{
//  std::vector < Client > clients; // bad

//  std::vector < Server > servers; // bad

//  std::vector < Router > routers; // bad

//  ---------------------------------------------------------

	[[maybe_unused]] Entity * entity_1 = new Client;

	[[maybe_unused]] Entity * entity_2 = new Server;

//	[[maybe_unused]] Entity * entity_3 = new Router; // error

//  ---------------------------------------------------------

	std::vector < Entity * > entities;

//  ---------------------------------------------------------

    entities.push_back(entity_1);

	entities.push_back(entity_2);

//  ---------------------------------------------------------

    for (auto entity : entities)
    {
        entity->test();
    }

//  ---------------------------------------------------------

    for (auto entity : entities)
    {
        delete entity;
    }
}

/////////////////////////////////////////////////////////////