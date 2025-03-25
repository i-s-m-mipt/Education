#include <cassert>
#include <iostream>

///////////////////////////////////////////////

class Entity
{
public :

	Entity(int x) : m_x(x) {}

//  -------------------------------------

	void test_v1() const 
    { 
        std::cout << "Entity::test_v1\n";
    }

protected :

    void test_v2() const 
    { 
        std::cout << "Entity::test_v2\n";
    }

private :

	int m_x = 0;
};

///////////////////////////////////////////////

class Client : public Entity
{
public :

	Client(int x, int y) : Entity(x), m_y(y) {}

//  -------------------------------------------

	void test_v1() const
	{
		std::cout << "Client::test_v1\n";

	//	test_v1(); // error

		Entity::test_v1();
	}

//  -------------------------------------------

	using Entity::test_v2;

private :

	int m_y = 0;
};

///////////////////////////////////////////////

int main()
{
    Entity entity(1);

//  --------------------------

    entity.test_v1();

//  entity.test_v2(); // error

//  --------------------------

	Client client(1, 1);

//  --------------------------

	client.test_v1();

	client.test_v2();
}