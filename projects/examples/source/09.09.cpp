///////////////////////////////////////////////////////////////////////

#include <memory>
#include <print>
#include <utility>

///////////////////////////////////////////////////////////////////////

class Entity 
{
public :

	virtual ~Entity() = default;

//  ---------------------------------

	virtual void test() const
	{ 
		std::print("Entity::test\n");
	}
};

///////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public :

	void test() const override 
	{ 
		std::print("Client::test\n");
	}
};

///////////////////////////////////////////////////////////////////////

int main()
{
	auto client_1 = std::make_unique < Client > ();

//	auto client_2 = client_1; // error

	auto client_3 = std::move(client_1);

//  -------------------------------------------------------------------

	std::unique_ptr < Entity > entity = std::make_unique < Client > ();

//  -------------------------------------------------------------------

	entity->test();
}

///////////////////////////////////////////////////////////////////////