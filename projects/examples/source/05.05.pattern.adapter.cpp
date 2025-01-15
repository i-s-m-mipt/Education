#include <iostream>

//////////////////////////////////////////////////////////////

class Client 
{ 
public:

	void test() const
	{ 
		std::cout << "Client::test\n"; 
	} 
};

//////////////////////////////////////////////////////////////

class Entity
{
public:

	virtual ~Entity() = default; 

//  ------------------------------

	virtual void test() const = 0;	
};

//////////////////////////////////////////////////////////////

class Adapter_v1 : public Entity
{
public:

	Adapter_v1(Client & client) : m_client(client) {}

//  ----------------------------------------------------------

	void test() const override 
	{ 
		m_client.test(); 
	}

private:

	Client & m_client;
};

//////////////////////////////////////////////////////////////

class Adapter_v2 : public Entity, private Client
{
public:

	void test() const override 
	{ 
		Client::test(); 
	}
};

//////////////////////////////////////////////////////////////

int main()
{	
	Client client;

	Entity * entity_1 = new Adapter_v1(client);

	entity_1->test();

	delete entity_1;

	Entity * entity_2 = new Adapter_v2;

	entity_2->test(); 
	
	delete entity_2;
}