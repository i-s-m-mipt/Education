////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Controller
{
protected :

	Controller(                         ) { ++s_counter; }

	Controller(const Controller < D > & ) { ++s_counter; }

	Controller(      Controller < D > &&) { ++s_counter; }

   ~Controller(                         ) { --s_counter; }

private :

	static inline auto s_counter = 0uz;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Entity_v1 : private Controller < Entity_v1 < T > > {};

template < typename T > class Entity_v2 : private Controller < Entity_v2 < T > > {};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Entity_v1 < int > entity_v1_1;
	
	Entity_v1 < int > entity_v1_2 = entity_v1_1;

//  --------------------------------------------

	Entity_v2 < int > entity_v2_1;

	Entity_v2 < int > entity_v2_2 = entity_v2_1;
}

////////////////////////////////////////////////////////////////////////////////////