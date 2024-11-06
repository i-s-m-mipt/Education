#include <iostream>

//  ================================================================================================

struct Client_v1 { static void test(); };
struct Client_v2 { static void test(); };

//  ================================================================================================

class Entity
{
	friend void            test();

	friend void Client_v1::test();

	friend      Client_v2;

//  ------------------------------------------------------------------------------------------------

	static void test()
	{
		std::clog << "Entity::test\n";
	} 	
};

//  ================================================================================================

void            test() { Entity::test(); }
void Client_v1::test() { Entity::test(); }
void Client_v2::test() { Entity::test(); }

//  ================================================================================================

int main()
{
			   test();
	Client_v1::test();
	Client_v2::test();
}