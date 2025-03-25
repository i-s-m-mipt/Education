#include <iostream>
#include <typeinfo>

///////////////////////////////////////////////////////////////////////////////

class Entity 
{
public :

	virtual ~Entity() = default;
};

///////////////////////////////////////////////////////////////////////////////

class Client : public Entity {};

///////////////////////////////////////////////////////////////////////////////

int main()
{
	auto x = 1, & y = x;
		
	Entity * entity = new Client;

//  ---------------------------------------------------------------------------

	std::cout << "main : typeid(      x) = " << typeid(      x).name() << '\n';

	std::cout << "main : typeid(      y) = " << typeid(      y).name() << '\n';

	std::cout << "main : typeid( entity) = " << typeid( entity).name() << '\n';

	std::cout << "main : typeid(*entity) = " << typeid(*entity).name() << '\n';

//  ---------------------------------------------------------------------------

	delete entity;
}