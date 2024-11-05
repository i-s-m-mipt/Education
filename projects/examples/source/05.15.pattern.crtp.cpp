#include <iostream>

//  ================================================================================================

template < typename D > struct Entity
{
	virtual ~Entity() = default;

//  ------------------------------------------------------------------------------------------------

	void test_v1() const
	{
		static_cast < const D * > (this)->test_v2();
	}

	void test_v2() const
	{ 
		std::clog << "Entity::test_v2\n"; 
	}
};

//  ================================================================================================

struct Client : public Entity < Client > {};

struct Server : public Entity < Server >
{
	void test_v2() const
	{ 
		std::clog << "Server::test_v2\n"; 
	}
}; 

//  ================================================================================================

template < typename E > void test(const E & entity)
{ 
	entity.test_v1(); 
}

//  ================================================================================================

int main()
{
	Client client; test(client);
	Server server; test(server);
}