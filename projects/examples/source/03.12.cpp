////////////////////////////////////////

#include <print>

////////////////////////////////////////

class Entity
{
public :

	void test_v1() const 
	{ 
		std::print("Entity::test_v1\n");
	}

protected :

	void test_v2() const 
	{ 
		std::print("Entity::test_v2\n");
	}
};

////////////////////////////////////////

class Server_v1 : private Entity 
{
public :

	void test() const
	{
		Entity::test_v1();

		Entity::test_v2();
	}
};

////////////////////////////////////////

class Server_v2 
{
public :

	void test() const
	{
		m_entity.test_v1();

	//	m_entity.test_v2(); // error
	}

private : 

	Entity m_entity;
};

////////////////////////////////////////

int main()
{
	Server_v1 server_v1;

//  -----------------------------

//	server_v1.test_v1(); // error

//	server_v1.test_v2(); // error

//  -----------------------------

	server_v1.test();

//  -----------------------------

	Server_v2 server_v2;

//  -----------------------------

//	server_v2.test_v1(); // error

//	server_v2.test_v2(); // error

//  -----------------------------

	server_v2.test();
}

////////////////////////////////////////