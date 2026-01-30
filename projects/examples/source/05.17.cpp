///////////////////////////////////////////

// chapter : Software Architecture Patterns

///////////////////////////////////////////

// section : Template Patterns

///////////////////////////////////////////

// content : Static Polymorphism

///////////////////////////////////////////

#include <print>

///////////////////////////////////////////

class Entity
{
public :

	virtual ~Entity() = default;

//  ------------------------------

	virtual void test() const = 0;
};

///////////////////////////////////////////

class Client_v1 : public Entity 
{ 
public :

	void test() const override 
	{ 
		std::print("Client_v1::test\n");
	} 
};

///////////////////////////////////////////

class Server_v1 : public Entity 
{ 
public :

	void test() const override 
	{ 
		std::print("Server_v1::test\n");
	} 
};

///////////////////////////////////////////

void test_v1(Entity const & entity)
{
	entity.test();
}

///////////////////////////////////////////

class Client_v2 
{ 
public :

	void test() const 
	{ 
		std::print("Client_v2::test\n");
	} 
};

///////////////////////////////////////////

class Server_v2 
{ 
public :

	void test() const 
	{ 
		std::print("Server_v2::test\n");
	} 
};

///////////////////////////////////////////

void test_v2(auto const & entity)
{
	entity.test();
}

///////////////////////////////////////////

int main()
{
	Entity * entity = new Client_v1;

//  --------------------------------

	test_v1(*entity);

//  --------------------------------

	delete entity;

//  --------------------------------

	test_v2(Client_v2());
}

///////////////////////////////////////////