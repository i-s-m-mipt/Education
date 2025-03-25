#include <iostream>
#include <memory>
#include <utility>

///////////////////////////////////////////////////////////////////////

class Entity 
{
public :

	virtual ~Entity() = default;

//  ----------------------------------

	virtual void test() const
	{ 
		std::cout << "Entity::test\n";
	}
};

///////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public :

	void test() const override 
	{ 
		std::cout << "Client::test\n";
	}
};

///////////////////////////////////////////////////////////////////////

int main()
{
	auto x = std::make_unique < int > (1);

	auto y = std::move(x);

//  -------------------------------------------------------------------

	std::unique_ptr < Entity > entity = std::make_unique < Client > ();

//  -------------------------------------------------------------------

	entity->test();
}