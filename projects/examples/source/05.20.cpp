//////////////////////////////////////////////////////////

// chapter : Patterns

//////////////////////////////////////////////////////////

// section : Static Polymorphism

//////////////////////////////////////////////////////////

// content : Mixin-Based Pattern Controller

//////////////////////////////////////////////////////////

#include <cassert>

//////////////////////////////////////////////////////////

template < typename D > class Controller
{
public :

	static auto get()
	{
		return s_counter;
	}

protected :

	Controller(                         ) { ++s_counter; }

	Controller(Controller < D > const & ) { ++s_counter; }

	Controller(Controller < D >       &&) { ++s_counter; }

   ~Controller(                         ) { --s_counter; }

private :

	static inline auto s_counter = 0uz;
};

//////////////////////////////////////////////////////////

class Entity_v1 : private Controller < Entity_v1 > {};

class Entity_v2 : private Controller < Entity_v2 > {};

//////////////////////////////////////////////////////////

int main()
{
	Entity_v1 entity_v1;

//  ----------------------------------------------

	assert(Controller < Entity_v1 > ::get() == 1);

	assert(Controller < Entity_v2 > ::get() == 0);

//  ----------------------------------------------

	Entity_v2 entity_v2;

//  ----------------------------------------------

	assert(Controller < Entity_v1 > ::get() == 1);

	assert(Controller < Entity_v2 > ::get() == 1);
}

//////////////////////////////////////////////////////////