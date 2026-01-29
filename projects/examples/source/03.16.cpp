/////////////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

/////////////////////////////////////////////////////////////

// section : Dynamic Polymorphism

/////////////////////////////////////////////////////////////

// content : Dynamic Polymorphism
//
// content : Virtual Functions
//
// content : Overriding Functions
//
// content : Specifiers virtual, override and final
//
// content : Upcasting Type Conversions
//
// content : Slicing Objects
//
// content : Virtual Destructors

/////////////////////////////////////////////////////////////

#include <print>
#include <vector>

/////////////////////////////////////////////////////////////

class Entity 
{
public :

// ~Entity() = default; // error

//  ------------------------------------

	virtual ~Entity()
	{
		std::print("Entity::~Entity\n");
	}

//  ------------------------------------

	virtual void test() const
	{ 
		std::print("Entity::test\n");
	}
};

/////////////////////////////////////////////////////////////

class Client : public Entity
{
public :

   ~Client() override
	{
		std::print("Client::~Client\n");
	}

//  ------------------------------------

	void test() const override final
	{ 
		std::print("Client::test\n");
	}
};

/////////////////////////////////////////////////////////////

class Server final : public Entity 
{
public:

   ~Server() override
	{
		std::print("Server::~Server\n");
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