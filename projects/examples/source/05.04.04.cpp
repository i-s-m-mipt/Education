////////////////////////////////////////////////////////////////////////////////////

#include <cassert>

////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Entity_v1 : private Controller < Entity_v1 < T > > {};

template < typename T > class Entity_v2 : private Controller < Entity_v2 < T > > {};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Entity_v1 < int > entity_v1;

//  ----------------------------------------------------------

	assert(Controller < Entity_v1 < int > > ::s_counter == 1);

	assert(Controller < Entity_v2 < int > > ::s_counter == 0);

//  ----------------------------------------------------------

	Entity_v2 < int > entity_v2;

//  ----------------------------------------------------------

	assert(Controller < Entity_v1 < int > > ::s_counter == 1);

	assert(Controller < Entity_v2 < int > > ::s_counter == 1);
}

////////////////////////////////////////////////////////////////////////////////////