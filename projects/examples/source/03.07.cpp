/////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

/////////////////////////////////////////////////////

// section : Interclass Relations

/////////////////////////////////////////////////////

// content : Composition, Aggregation and Association
//
// content : Forward Declarations
//
// content : Dependency
//
// content : Stream std::cout

/////////////////////////////////////////////////////

#include <cassert>
#include <iostream>

/////////////////////////////////////////////////////

class Entity
{
public :

	Entity(int x) : m_x(x) {}

//  ----------------------------------

	void test() const
	{
		std::cout << "Entity::test\n";
	}

//  ----------------------------------

	static inline auto s_x = 1;

private :

	int m_x = 0;
};

/////////////////////////////////////////////////////

struct Server;

/////////////////////////////////////////////////////

struct Client { Server * server = nullptr; };

struct Server { Client * client = nullptr; };

/////////////////////////////////////////////////////

int main()
{
	Entity entity_1(1);
	
	Entity entity_2(2);

//  -------------------------

	assert(Entity::s_x == 1);

//  -------------------------

	Client client;

	Server server;

//  -------------------------

	server.client = &client;

	client.server = &server;

//  -------------------------

	Entity(1).test();
}

/////////////////////////////////////////////////////