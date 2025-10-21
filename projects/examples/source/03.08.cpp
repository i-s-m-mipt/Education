/////////////////////////////////////////////////

#include <print>

/////////////////////////////////////////////////

class Client_v1 { public : static void test(); };

class Client_v2 { public : static void test(); };

/////////////////////////////////////////////////

class Entity
{
private :

	friend void test();

//  ---------------------------------

	friend void Client_v1::test();

//  ---------------------------------

	friend Client_v2;

//  ---------------------------------

	static void test()
	{
		std::print("Entity::test\n");
	}
};

/////////////////////////////////////////////////

void            test() { Entity::test(); }

void Client_v1::test() { Entity::test(); }

void Client_v2::test() { Entity::test(); }

/////////////////////////////////////////////////

int main()
{
//	Entity::test(); // error

//  ------------------------

	test();

//  ------------------------
			   
	Client_v1::test();

	Client_v2::test();
}

/////////////////////////////////////////////////