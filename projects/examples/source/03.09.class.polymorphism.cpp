#include <iostream>
#include <vector>

//  ================================================================================================

class Entity 
{
public:

	Entity()
	{
//		test_v1(); // bad
	}

// ~Entity() = default; // error

	virtual ~Entity() = default;

//  -----------------------------------------

	virtual void test_v1() const
	{ 
		std::cout << "Entity::test_v1\n"; 
	}

	virtual void test_v2() const = 0;

//	virtual void test_v3() const = 0 // error
//	{
//		std::cout << "Entity::test_v3\n";
//	}

private:

	void * data = nullptr;
};

//  ================================================================================================

void Entity::test_v2() const
{ 
	std::cout << "Entity::test_v2\n"; 
}

//  ================================================================================================

class Client : public Entity
{
public:

	void test_v1() const override final 
	{ 
		std::cout << "Client::test_v1\n";                    
	}

	void test_v2() const override 
	{ 
		std::cout << "Client::test_v2\n"; Entity::test_v2(); 
	}

private:

	void * data = nullptr;
};

//  ================================================================================================

class Server final : public Entity 
{
public:

	void test_v2() const override 
	{ 
		std::cout << "Server::test_v2\n"; 

		Entity::test_v2();
	}

private:

	void * data = nullptr;
};

//  ================================================================================================

class Router : private Entity 
{
public:

	void test_v2() const override 
	{ 
		std::cout << "Router::test_v2\n"; 

		Entity::test_v2();
	}
};

//  ================================================================================================

int main()
{
	Client client;

	[[maybe_unused]] Entity * entity_1 = &client;
	[[maybe_unused]] Entity & entity_2 =  client;
//	[[maybe_unused]] Entity   entity_3 =  client; // error

	entity_1->test_v1(); // support: compiler-explorer.com

//  ------------------------------------------------------

	std::vector < Entity * > entities 
	{ 
		new Client(), 
		new Server() 
	};

	for (auto entity : entities) 
	{
		entity->test_v1();
		entity->test_v2();

		delete entity;
	}
	
//  --------------

	Router router;

//	[[maybe_unused]] Entity * entity_4 = &router; // error

//  -----------------------------------------------------------

	std::cout << "sizeof(Entity) = " << sizeof(Entity) << '\n';
	std::cout << "sizeof(Client) = " << sizeof(Client) << '\n';
	std::cout << "sizeof(Server) = " << sizeof(Server) << '\n';
	std::cout << "sizeof(Router) = " << sizeof(Router) << '\n';
}