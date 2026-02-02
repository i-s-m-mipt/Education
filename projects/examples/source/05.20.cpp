//////////////////////////////////////////////////////////

// chapter : Software Design Patterns

//////////////////////////////////////////////////////////

// section : Mixin-Based Patterns

//////////////////////////////////////////////////////////

// content : Mixin-Based Pattern Controller

//////////////////////////////////////////////////////////

#include <cassert>

//////////////////////////////////////////////////////////

template < typename D > class Controller
{
public :

	static inline auto s_counter = 0uz;

protected :

	Controller(                         ) { ++s_counter; }

	Controller(Controller < D > const & ) { ++s_counter; }

	Controller(Controller < D >       &&) { ++s_counter; }

   ~Controller(                         ) { --s_counter; }
};

//////////////////////////////////////////////////////////

class Entity_v1 : private Controller < Entity_v1 > {};

class Entity_v2 : private Controller < Entity_v2 > {};

//////////////////////////////////////////////////////////

int main()
{
	Entity_v1 entity_v1;

//  --------------------------------------------------

	assert(Controller < Entity_v1 > ::s_counter == 1);

	assert(Controller < Entity_v2 > ::s_counter == 0);

//  --------------------------------------------------

	Entity_v2 entity_v2;

//  --------------------------------------------------

	assert(Controller < Entity_v1 > ::s_counter == 1);

	assert(Controller < Entity_v2 > ::s_counter == 1);
}

//////////////////////////////////////////////////////////