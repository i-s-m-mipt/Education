#include <cstddef>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Controller
{
protected :

	Controller(                         ) { ++s_counter; }

	Controller(const Controller < D > & ) { ++s_counter; }

	Controller(      Controller < D > &&) { ++s_counter; }

   ~Controller() 
    { 
		--s_counter;
	}

private :

	static inline auto s_counter = 0uz;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Entity_v3 : private Controller < Entity_v3 < T > > {};

template < typename T > class Entity_v4 : private Controller < Entity_v4 < T > > {};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Entity_v3 < int > entity_v3_1;
	
	Entity_v3 < int > entity_v3_2(entity_v3_1);

//  -------------------------------------------

	Entity_v4 < int > entity_v4;
}