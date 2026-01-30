//////////////////////////////////////////////////////////////

// chapter : Generic Programming

//////////////////////////////////////////////////////////////

// section : Forwarding References

//////////////////////////////////////////////////////////////

// content : Forwarding References
//
// content : Perfect Forwarding
//
// content : Function std::forward

//////////////////////////////////////////////////////////////

#include <print>
#include <utility>

//////////////////////////////////////////////////////////////

struct Entity {};

//////////////////////////////////////////////////////////////

void test_v1(Entity       & ) { std::print("test_v1 (1)\n"); }

void test_v1(Entity const & ) { std::print("test_v1 (2)\n"); }

void test_v1(Entity       &&) { std::print("test_v1 (3)\n"); }

//////////////////////////////////////////////////////////////

void test_v2(Entity       & entity) { test_v1(entity); }

void test_v2(Entity const & entity) { test_v1(entity); }

//////////////////////////////////////////////////////////////

void test_v2(Entity && entity)
{ 
	test_v1(std::move(entity));
}

//////////////////////////////////////////////////////////////

template < typename E > void test_v3(E && entity) 
{ 
	test_v1(std::forward < E > (entity));
}

//////////////////////////////////////////////////////////////

int main()
{
	Entity       entity_1;

	Entity const entity_2;

//  -----------------------------

	test_v2(entity_1);

	test_v2(entity_2);

//  -----------------------------

	test_v2(std::move(entity_1));

//  -----------------------------

	test_v3(entity_1);

	test_v3(entity_2);

//  -----------------------------
	
	test_v3(std::move(entity_1));
}

//////////////////////////////////////////////////////////////