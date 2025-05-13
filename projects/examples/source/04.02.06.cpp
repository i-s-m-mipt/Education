////////////////////////////////////////////////////////////////////////////////////

#include <cassert>

////////////////////////////////////////////////////////////////////////////////////

#include <boost/type_index.hpp>

////////////////////////////////////////////////////////////////////////////////////

struct Entity {};

////////////////////////////////////////////////////////////////////////////////////

auto         make_entity_v1() { return Entity(); }

auto const   make_entity_v2() { return Entity(); }

////////////////////////////////////////////////////////////////////////////////////

auto       & make_entity_v3() { static Entity       entity; return entity; }

auto const & make_entity_v4() { static Entity const entity; return entity; }

////////////////////////////////////////////////////////////////////////////////////

template < typename E > auto make_typename_v1(E entity) 
{
	return boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name();
}

////////////////////////////////////////////////////////////////////////////////////

template < typename E > auto make_typename_v2(E & entity) 
{
	return boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name();
}

////////////////////////////////////////////////////////////////////////////////////

template < typename E > auto make_typename_v3(E const & entity) 
{
	return boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name();
}

////////////////////////////////////////////////////////////////////////////////////

template < typename E > auto make_typename_v4(E && entity) 
{
	return boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name();
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	assert(make_typename_v1(make_entity_v1()) == "Entity"        );

	assert(make_typename_v1(make_entity_v2()) == "Entity"        );

	assert(make_typename_v1(make_entity_v3()) == "Entity"        );

	assert(make_typename_v1(make_entity_v4()) == "Entity"        );

//  ------------------------------------------------------------------------

//	assert(make_typename_v2(make_entity_v1()) == "Entity&"       ); // error

	assert(make_typename_v2(make_entity_v2()) == "Entity const&" );

	assert(make_typename_v2(make_entity_v3()) == "Entity&"       );

	assert(make_typename_v2(make_entity_v4()) == "Entity const&" );

//  ------------------------------------------------------------------------

	assert(make_typename_v3(make_entity_v1()) == "Entity const&" );

	assert(make_typename_v3(make_entity_v2()) == "Entity const&" );

	assert(make_typename_v3(make_entity_v3()) == "Entity const&" );

	assert(make_typename_v3(make_entity_v4()) == "Entity const&" );

//  ------------------------------------------------------------------------

	assert(make_typename_v4(make_entity_v1()) == "Entity&&"      );

	assert(make_typename_v4(make_entity_v2()) == "Entity const&&");

	assert(make_typename_v4(make_entity_v3()) == "Entity&"       );

	assert(make_typename_v4(make_entity_v4()) == "Entity const&" );
}

////////////////////////////////////////////////////////////////////////////////////