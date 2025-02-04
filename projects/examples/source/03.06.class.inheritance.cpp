#include <cassert>
#include <iostream>

///////////////////////////////////////////////////////////////////

class Entity
{
public:

	Entity() = default;

	Entity(int x) : m_data(x) {}

//  ----------------------------------------------------------

	void test_v1() const { std::cout << "Entity::test_v1\n"; }

	void test_v2() const { std::cout << "Entity::test_v2\n"; }

protected:

	auto data() const
	{ 
		return m_data; 
	}

private:

	int m_data = 0;
};

///////////////////////////////////////////////////////////////////

class Client : public Entity
{
public:

	Client(int x, int y) : Entity(x), m_data(y)
	{
		assert(data() == x);
	}

//  ---------------------------------------------------------------

	void test_v1() const
	{
		std::cout << "Client::test_v1\n";

	//	test_v1(); // error

		Entity::test_v1();
	}

//  ---------------------------------------------------------------

	using Entity::data;

private:

	int m_data = 0;
};

///////////////////////////////////////////////////////////////////

class Server_v1 : private Entity 
{
public:

	void test() const
	{ 
		test_v1(); 

		test_v2(); 
	}
};

///////////////////////////////////////////////////////////////////

class Server_v2 
{
public:

	void test() const
	{ 
		m_entity.test_v1(); 

		m_entity.test_v2(); 
	}

private: 

	Entity m_entity; 
};

///////////////////////////////////////////////////////////////////

int main()
{
	{
//		assert(Entity(1).data() == 1); // error
	}

//  -------------------------------------------

	{
		Client client(1, 1);

		client.test_v1();

		client.test_v2();

		assert(client.data() == 1);
	}

//  -------------------------------------------

	{	
		Server_v1 server_v1;

//		server_v1.test_v1(); // error

//		server_v1.test_v2(); // error

		server_v1.test();
	}

//  -------------------------------------------

	{
		Server_v2().test();
	}
}