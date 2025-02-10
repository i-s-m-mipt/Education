#include <cassert>
#include <iostream>
#include <utility>

//////////////////////////////////////////////////////////////////////////////////////

struct Entity {};

//////////////////////////////////////////////////////////////////////////////////////

void test_v1(      Entity & ) { std::cout << "test_v1 (1)\n"; }

void test_v1(const Entity & ) { std::cout << "test_v1 (2)\n"; }

void test_v1(      Entity &&) { std::cout << "test_v1 (3)\n"; }

//////////////////////////////////////////////////////////////////////////////////////

void test_v2(      Entity &  entity) { test_v1(entity); }

void test_v2(const Entity &  entity) { test_v1(entity); }

void test_v2(      Entity && entity) 
{ 
    test_v1(std::move(entity));
}

//////////////////////////////////////////////////////////////////////////////////////

template < typename E > void test_v3(E && entity) 
{ 
	test_v1(std::forward < E > (entity));
}

//////////////////////////////////////////////////////////////////////////////////////

auto test_v4(int x, int y) 
{ 
	return x + y;
}

//////////////////////////////////////////////////////////////////////////////////////

template < typename F, typename ... Ts > decltype(auto) invoke(F && f, Ts && ... xs) 
{ 
	return f(std::forward < Ts > (xs)...);
}

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		Entity entity_1;

		test_v2(entity_1);

		test_v3(entity_1);

		const Entity entity_2;

		test_v2(entity_2);

		test_v3(entity_2);

		Entity entity_3;

		test_v2(std::move(entity_3));
	
		test_v3(std::move(entity_3));
	}
	
//  ---------------------------------------

	{
		assert(invoke(test_v4, 1, 2) == 3);
	}
}