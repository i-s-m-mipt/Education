/////////////////////////////////////////////////////////////////////////////////

#include <cassert>

/////////////////////////////////////////////////////////////////////////////////

#include <boost/type_index.hpp>

/////////////////////////////////////////////////////////////////////////////////

class Entity 
{
public :

	virtual ~Entity() = default;
};

/////////////////////////////////////////////////////////////////////////////////

class Client : public Entity {};

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto x = 1, & y = x;
		
	Entity * entity = new Client;

//  -----------------------------------------------------------------------------

	using boost::typeindex::type_id_with_cvr;

//  -----------------------------------------------------------------------------

	assert(type_id_with_cvr < decltype(      x) > ().pretty_name() == "int"    );
	
	assert(type_id_with_cvr < decltype(      y) > ().pretty_name() == "int&"   );

	assert(type_id_with_cvr < decltype( entity) > ().pretty_name() == "Entity*");

	assert(type_id_with_cvr < decltype(*entity) > ().pretty_name() == "Entity&");

//  -----------------------------------------------------------------------------

	delete entity;
}

/////////////////////////////////////////////////////////////////////////////////