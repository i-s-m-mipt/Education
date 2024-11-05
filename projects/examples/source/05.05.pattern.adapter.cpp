#include <iostream>

//  ================================================================================================

struct Client 
{ 
	void test()
	{ 
		std::clog << "Client::test\n"; 
	} 
};

//  ================================================================================================

struct Entity
{
	virtual ~Entity() = default; 

	virtual void test() const = 0;	
};

//  ================================================================================================

class Adapter : public Entity
{
public:

	explicit Adapter(Client & client) : m_client(client) {}

//  ------------------------------------------------------------------------------------------------

	void test() const override 
	{ 
		m_client.test(); 
	}

private:

	Client & m_client;
};

//  ================================================================================================

int main()
{	
	Client client;

	Entity * entity = new Adapter(client);

	entity->test(); 
	
	delete entity;
}