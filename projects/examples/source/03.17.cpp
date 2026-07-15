/////////////////////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

/////////////////////////////////////////////////////////////////////

// content : Virtual Pointers and Tables

/////////////////////////////////////////////////////////////////////

#include <print>

/////////////////////////////////////////////////////////////////////

class Entity
{
public :

	virtual ~Entity() = default;

//  -----------------------------------------------------------------

	virtual void test_v1() const { std::print("Entity::test_v1\n"); }

	virtual void test_v2() const { std::print("Entity::test_v2\n"); }
};

/////////////////////////////////////////////////////////////////////

class Client : public Entity
{
public:

	void test_v1() const override
	{
		std::print("Client::test_v1\n");
	}
};

/////////////////////////////////////////////////////////////////////

class Server : public Entity
{
public:

	void test_v2() const override
	{
		std::print("Server::test_v2\n");
	}
};

/////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(sizeof(Entity) == sizeof(void *));

	static_assert(sizeof(Client) == sizeof(void *));

	static_assert(sizeof(Server) == sizeof(void *));

//  -------------------------------------------------------------

	Entity * entity = new Client;

//  -------------------------------------------------------------

	entity->test_v1(); // support : https://compiler-explorer.com

//  -------------------------------------------------------------

	delete entity;
}

/////////////////////////////////////////////////////////////////////