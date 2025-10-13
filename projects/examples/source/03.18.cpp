///////////////////////////////////////////////////////////

#include <iostream>

///////////////////////////////////////////////////////////

class Entity_v1
{
private : 

	void * m_x = nullptr;
};

///////////////////////////////////////////////////////////

class Client_v1 : public Entity_v1
{ 
private : 
	
	void * m_y = nullptr;
};

///////////////////////////////////////////////////////////

class Entity_v2
{ 
public :

	virtual ~Entity_v2() = default;

//  -------------------------------------

	virtual void test() const
	{ 
		std::cout << "Entity_v2::test\n";
	}

private : 

	void * m_x = nullptr;
};

///////////////////////////////////////////////////////////

class Client_v2 : public Entity_v2
{
public:

	void test() const override
	{ 
		std::cout << "Client_v2::test\n";
	}

private : 
	
	void * m_y = nullptr;
};

///////////////////////////////////////////////////////////

int main()
{
	static_assert(sizeof(Entity_v1) == 1 * sizeof(void *));

	static_assert(sizeof(Client_v1) == 2 * sizeof(void *));

//  -------------------------------------------------------

	static_assert(sizeof(Entity_v2) == 2 * sizeof(void *));

	static_assert(sizeof(Client_v2) == 3 * sizeof(void *));

//  -------------------------------------------------------

	Entity_v2 * entity_v2 = new Client_v2;

//  -------------------------------------------------------

	entity_v2->test(); // support : compiler-explorer.com

//  -------------------------------------------------------

	delete entity_v2;
}

///////////////////////////////////////////////////////////