////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Controller
{
protected :

	Controller(                         ) { ++s_counter; }

	Controller(Controller < D > const & ) { ++s_counter; }

	Controller(Controller < D >       &&) { ++s_counter; }

   ~Controller(                         ) { --s_counter; }

private :

	static inline auto s_counter = 0uz;
};

////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Entity_v1 : private Controller < Entity_v1 < T > > {};

template < typename T > class Entity_v2 : private Controller < Entity_v2 < T > > {};

////////////////////////////////////////////////////////////////////////////////////

template < typename E > void test()
{
	E entity_1;

	E entity_2 = entity_1;
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	test < Entity_v1 < int > > ();

	test < Entity_v2 < int > > ();
}

////////////////////////////////////////////////////////////////////////////////////