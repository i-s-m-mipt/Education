////////////////////////////////////////////////////////////////

#include <print>
#include <vector>

////////////////////////////////////////////////////////////////

template < typename D > class Entity
{
public :

	void test() const
	{
		static_cast < D const * > (this)->test_implementation();
	}

protected :

	void test_implementation() const
	{ 
		std::print("Entity::test_implementation\n");
	}
};

////////////////////////////////////////////////////////////////

class Client : public Entity < Client > {};

////////////////////////////////////////////////////////////////

class Server : public Entity < Server >
{
public :

	void test_implementation() const
	{ 
		std::print("Server::test_implementation\n");
	}
};

////////////////////////////////////////////////////////////////

template < typename D > void test(Entity < D > const & entity) 
{
	entity.test();
}

////////////////////////////////////////////////////////////////

int main()
{
	test(Client());
	
	test(Server());

//  -------------------------------------------

//	std::vector < Entity * > entities; // error
}

////////////////////////////////////////////////////////////////