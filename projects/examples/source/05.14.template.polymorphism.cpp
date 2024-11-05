#include <iostream>

//  ================================================================================================

struct Entity
{
	virtual ~Entity() = default;

	virtual void test() const = 0;
};

//  ================================================================================================

struct Client_v1 : public Entity 
{ 
	void test() const override 
	{ 
		std::clog << "Client_v1::test\n"; 
	} 
};

//  ================================================================================================

struct Server_v1 : public Entity 
{ 
	void test() const override 
	{ 
		std::clog << "Server_v1::test\n"; 
	} 
};

//  ================================================================================================

void test_v1(const Entity & entity)
{
	entity.test(); 
}

//  ================================================================================================

struct Client_v2 { void test() const { std::clog << "Client_v2::test\n"; } };
struct Server_v2 { void test() const { std::clog << "Server_v2::test\n"; } };

//  ================================================================================================

template < typename E > void test_v2(const E & entity)
{
	entity.test();
}

//  ================================================================================================

int main()
{
	Entity * entity = new Client_v1();

	test_v1(*entity);

	delete entity;

	Client_v2 client_v2; 
	
	test_v2(client_v2);
}