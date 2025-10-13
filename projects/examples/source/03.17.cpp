/////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

/////////////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  -----------------------------------------

    virtual void test_v1() const = 0;

//  -----------------------------------------

//	virtual void test_v2() const = 0 // error
//	{
//		std::cout << "Entity::test_v2\n";
//	}
};

/////////////////////////////////////////////////////////////

void Entity::test_v1() const
{ 
	std::cout << "Entity::test_v1\n";
}

/////////////////////////////////////////////////////////////

class Client : public Entity
{
public :

    void test_v1() const override 
	{ 
		std::cout << "Client::test_v1\n";
		
		Entity::test_v1();
	}
};

/////////////////////////////////////////////////////////////

class Server : public Entity
{
public :

    void test_v1() const override 
	{ 
		std::cout << "Server::test_v1\n";
		
		Entity::test_v1();
	}
};

/////////////////////////////////////////////////////////////

int main()
{
	[[maybe_unused]] Entity * entity_1 = new Client;

	[[maybe_unused]] Entity * entity_2 = new Server;

//	[[maybe_unused]] Entity * entity_3 = new Entity; // error

//  ---------------------------------------------------------

    std::vector < Entity * > entities;

//  ---------------------------------------------------------

    entities.push_back(entity_1);

    entities.push_back(entity_2);

//  ---------------------------------------------------------

    for (auto entity : entities)
    {
        entity->test_v1(); // support : compiler-explorer.com
    }

//  ---------------------------------------------------------

    for (auto entity : entities)
    {
        delete entity;
    }
}

/////////////////////////////////////////////////////////////