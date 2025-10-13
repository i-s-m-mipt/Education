//////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////

class Entity
{
public :

	Entity(int x) : m_x(x)
	{
		std::cout << "Entity::Entity\n";
	}

//  ----------------------------------------------------------

	void test_v1() const { std::cout << "Entity::test_v1\n"; }

	void test_v2() const { std::cout << "Entity::test_v2\n"; }

protected :

    void test_v3() const 
	{ 
		std::cout << "Entity::test_v3\n"; 
	}

private :

	int m_x = 0;
};

//////////////////////////////////////////////////////////////

class Client : public Entity
{
public :

	Client(int x, int y) : Entity(x), m_y(y)
	{
		std::cout << "Client::Client\n";
	}

//  ----------------------------------------

	void test_v2() const
	{
		std::cout << "Client::test_v2\n";

	//	test_v2(); // error

		Entity::test_v2();
	}

//  ----------------------------------------

	using Entity::test_v3;

private :

	int m_y = 0;
};

//////////////////////////////////////////////////////////////

int main()
{
    Entity entity(1);

//  -------------------------------------------------

	static_assert(sizeof(Entity) == 1 * sizeof(int));

//  -------------------------------------------------

    entity.test_v1();

	entity.test_v2();

//  entity.test_v3(); // error

//  -------------------------------------------------

	Client client(1, 1);

//  -------------------------------------------------

	static_assert(sizeof(Client) == 2 * sizeof(int));

//  -------------------------------------------------

	client.test_v1();

	client.test_v2();

	client.test_v3();
}

//////////////////////////////////////////////////////////////