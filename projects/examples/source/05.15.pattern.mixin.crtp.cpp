#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////

template < typename D > class Entity
{
public:

	void test() const
	{
		static_cast < const D * > (this)->test_implementation();
	}

	void test_implementation() const
	{ 
		std::clog << "Entity::test_implementation\n"; 
	}
};

////////////////////////////////////////////////////////////////

class Client : public Entity < Client > {};

class Server : public Entity < Server >
{
public:

	void test_implementation() const
	{ 
		std::clog << "Server::test_implementation\n"; 
	}
}; 

////////////////////////////////////////////////////////////////

template < typename D > void test(const Entity < D > & entity) 
{
	entity.test();
}

////////////////////////////////////////////////////////////////

int main()
{
	Client client; test(client);
	Server server; test(server);

//	std::vector < Entity * > entities; // error
}