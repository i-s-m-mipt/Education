#include <iostream>
#include <vector>

//  ================================================================================================

struct Entity 
{
	Entity()
	{
//		test_v1(); // bad
	}

// ~Entity() = default; // error

	virtual ~Entity() = default;

//  ------------------------------------------------------------------------------------------------

	virtual void test_v1() const
	{ 
		std::clog << "Entity::test_v1\n"; 
	}

	virtual void test_v2() const = 0;

//	virtual void test_v3() const = 0 // error
//	{
//		std::clog << "Entity::test_v3\n";
//	}

	void * data = nullptr;
};

//  ================================================================================================

void Entity::test_v2() const
{ 
	std::clog << "Entity::test_v2\n"; 
}

//  ================================================================================================

struct Client : public Entity
{
	void test_v1() const override final 
	{ 
		std::clog << "Client::test_v1\n";                    
	}

	void test_v2() const override 
	{ 
		std::clog << "Client::test_v2\n"; Entity::test_v2(); 
	}

//  ------------------------------------------------------------------------------------------------

	void * data = nullptr;
};

//  ================================================================================================

struct Server final : public Entity 
{
	void test_v2() const override 
	{ 
		std::clog << "Server::test_v2\n"; 

		Entity::test_v2();
	}

//  ------------------------------------------------------------------------------------------------

	void * data = nullptr;
};

//  ================================================================================================

struct Router : private Entity 
{
	void test_v2() const override 
	{ 
		std::clog << "Router::test_v2\n"; 

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

//  ------------------------------------------------------------------------------------------------

	std::vector < Entity * > entities 
	(
		{ 
			new Client(), 
			new Server() 
		}
	);

	for (auto entity : entities) 
	{
		entity->test_v1();
		entity->test_v2();

		delete entity;
	}
	
//  ------------------------------------------------------------------------------------------------

	Router router;

//	[[maybe_unused]] Entity * entity_4 = &router; // error

//  ------------------------------------------------------------------------------------------------

	std::cout << "sizeof(Entity) = " << sizeof(Entity) << '\n';
	std::cout << "sizeof(Client) = " << sizeof(Client) << '\n';
	std::cout << "sizeof(Server) = " << sizeof(Server) << '\n';
	std::cout << "sizeof(Router) = " << sizeof(Router) << '\n';
}