#include <cassert>
#include <tuple>

///////////////////////////////////////////////////////////////////////////////////////

// support : Boost.Conversion

///////////////////////////////////////////////////////////////////////////////////////

class Entity 
{
public :

	virtual ~Entity() = default;
};

///////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity {};

class Server : public Entity {};

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Entity * entity = new Client;

//  -----------------------------------------------------------------------------------

//	assert( static_cast < Client * > (entity) != 0); // bad

	assert(dynamic_cast < Client * > (entity) != 0); // support : compiler-explorer.com

	assert(dynamic_cast < Server * > (entity) == 0);

//  -----------------------------------------------------------------------------------

	delete entity;

//  -----------------------------------------------------------------------------------

	[[maybe_unused]] auto x = 1.0;

//	assert(dynamic_cast < int > (x) == 1); // error
}