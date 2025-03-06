#include <cassert>
#include <tuple>

//////////////////////////////////////////////////////////////////////////////////

class Entity 
{
public:

	virtual ~Entity() = default;
};

//////////////////////////////////////////////////////////////////////////////////

class Client : public Entity {};

class Server : public Entity {};

//////////////////////////////////////////////////////////////////////////////////

int main()
{
	Entity * entity = new Client;

//  ------------------------------------------------------------------------------

//	assert(  static_cast < Client * > (entity)); // bad

	assert( dynamic_cast < Client * > (entity)); // support: compiler-explorer.com

	assert(!dynamic_cast < Server * > (entity));

//  ------------------------------------------------------------------------------

	delete entity;

//  ------------------------------------------------------------------------------

	[[maybe_unused]] auto x = 1.0;

//	std::ignore = dynamic_cast < int > (x); // error
}