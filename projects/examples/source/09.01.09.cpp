#include <iostream>
#include <memory>
#include <utility>

//////////////////////////////////////////////////////////////////////

class Entity 
{
public:

	virtual ~Entity() = default;

//  ----------------------------------

	virtual void test() const
	{ 
		std::cout << "Entity::test\n";
	}
};

//////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public:

	void test() const override 
	{ 
		std::cout << "Client::test\n";
	}
};

//////////////////////////////////////////////////////////////////////

int main()
{
	auto ptr_1 = std::make_unique < int > (1);

	auto ptr_2 = std::move(ptr_1);

//  ------------------------------------------------------------------

	std::unique_ptr < Entity > ptr_3 = std::make_unique < Client > ();

//  ------------------------------------------------------------------

	ptr_3->test();
}