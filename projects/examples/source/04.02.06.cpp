//////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/type_index.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////

struct Entity {};

//////////////////////////////////////////////////////////////////////////////////////////////////

auto         make_entity_v1() { return Entity(); }

auto const   make_entity_v2() { return Entity(); }

//////////////////////////////////////////////////////////////////////////////////////////////////

auto       & make_entity_v3() { static Entity       entity; return entity; }

auto const & make_entity_v4() { static Entity const entity; return entity; }

//////////////////////////////////////////////////////////////////////////////////////////////////

template < typename E > void test_v1(E entity) 
{
	std::cout << "test_v1 : typeid(entity) = ";

	std::cout << boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name() << '\n';
}

//////////////////////////////////////////////////////////////////////////////////////////////////

template < typename E > void test_v2(E & entity) 
{
	std::cout << "test_v2 : typeid(entity) = ";

	std::cout << boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name() << '\n';
}

//////////////////////////////////////////////////////////////////////////////////////////////////

template < typename E > void test_v3(E const & entity) 
{
	std::cout << "test_v3 : typeid(entity) = ";

	std::cout << boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name() << '\n';
}

//////////////////////////////////////////////////////////////////////////////////////////////////

template < typename E > void test_v4(E && entity) 
{
	std::cout << "test_v4 : typeid(entity) = ";

	std::cout << boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name() << '\n';
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	test_v1(make_entity_v1());

	test_v1(make_entity_v2());

	test_v1(make_entity_v3());

	test_v1(make_entity_v4());

//  -----------------------------------

//	test_v2(make_entity_v1()); // error

	test_v2(make_entity_v2());

	test_v2(make_entity_v3());

	test_v2(make_entity_v4());

//  -----------------------------------

	test_v3(make_entity_v1());

	test_v3(make_entity_v2());

	test_v3(make_entity_v3());

	test_v3(make_entity_v4());

//  -----------------------------------

	test_v4(make_entity_v1());

	test_v4(make_entity_v2());

	test_v4(make_entity_v3());

	test_v4(make_entity_v4());
}

//////////////////////////////////////////////////////////////////////////////////////////////////