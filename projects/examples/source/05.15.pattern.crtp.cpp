#include <iostream>

//  ================================================================================================

template < typename D > struct Entity
{
	virtual ~Entity() = default;

//  ------------------------------------------------------------------------------------------------

	void test() const
	{
		static_cast < const D * > (this)->test_implementation();
	}

	void test_implementation() const
	{ 
		std::clog << "Entity::test_implementation\n"; 
	}
};

//  ================================================================================================

struct Client : public Entity < Client > {};

struct Server : public Entity < Server >
{
	void test_implementation() const
	{ 
		std::clog << "Server::test_implementation\n"; 
	}
}; 

//  ================================================================================================

template < typename E > void test(const E & entity)
{ 
	entity.test(); 
}

//  ================================================================================================

int main()
{
	Client client; test(client);
	Server server; test(server);
}