#include <iostream>
#include <utility>

#include <boost/type_index.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////

struct Entity {};

//////////////////////////////////////////////////////////////////////////////////////////////////

      auto & make_entity_v1() { static       Entity entity; return entity; }

const auto & make_entity_v2() { static const Entity entity; return entity; }

      auto   make_entity_v3() { return Entity(); }

const auto   make_entity_v4() { return Entity(); }

//////////////////////////////////////////////////////////////////////////////////////////////////

template < typename E > void test_v1(E entity) 
{
	std::cout << "test_v1 : typeid(entity) = ";

	std::cout << boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name() << '\n';
}

template < typename E > void test_v2(E & entity) 
{
	std::cout << "test_v2 : typeid(entity) = ";

	std::cout << boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name() << '\n';
}

template < typename E > void test_v3(const E & entity) 
{
	std::cout << "test_v3 : typeid(entity) = ";

	std::cout << boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name() << '\n';
}

template < typename E > void test_v4(E && entity) 
{
	std::cout << "test_v4 : typeid(entity) = ";

	std::cout << boost::typeindex::type_id_with_cvr < decltype(entity) > ().pretty_name() << '\n';
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto &  lr__entity = make_entity_v1(); 
	auto &  lr_centity = make_entity_v2(); 
	auto && rr__entity = make_entity_v3(); 
	auto && rr_centity = make_entity_v4();

//  --------------------------------------

	test_v1(lr__entity);
	test_v1(lr_centity);
	test_v1(rr__entity);
	test_v1(rr_centity);

//  --------------------

	test_v2(lr__entity);
	test_v2(lr_centity);
	test_v2(rr__entity);
	test_v2(rr_centity);

//  --------------------

	test_v3(lr__entity);
	test_v3(lr_centity);
	test_v3(rr__entity);
	test_v3(rr_centity);

//  --------------------

	test_v4(lr__entity);
	test_v4(lr_centity);
	test_v4(rr__entity);
	test_v4(rr_centity);
	
//  ---------------------------

	Entity entity;

	test_v4(entity);

	test_v4(std::move(entity));
}