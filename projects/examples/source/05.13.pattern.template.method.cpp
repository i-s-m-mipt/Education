#include <iostream>

//  ================================================================================================

class Entity
{
public:

	virtual ~Entity() = default; 

//  ------------------------------------------------------------------------------------------------

	void template_method() const
	{ 
		test_v1(); 
		test_v2(); 
		test_v3(); 
		test_v4();
	} 

//  ------------------------------------------------------------------------------------------------

private:

	void test_v1() const { std::clog << "Entity::test_v1\n"; }
	void test_v3() const { std::clog << "Entity::test_v3\n"; }

//  ------------------------------------------------------------------------------------------------

	virtual void test_v2() const = 0;
	virtual void test_v4() const = 0;
};

//  ================================================================================================

class Client : public Entity 
{ 
	void test_v2() const override { std::clog << "Client::test_v2\n"; }
	void test_v4() const override { std::clog << "Client::test_v4\n"; }  
};

//  ================================================================================================

class Server : public Entity
{
	void test_v2() const override { std::clog << "Server::test_v2\n"; }
	void test_v4() const override { std::clog << "Server::test_v4\n"; } 
};

//  ================================================================================================

int main()
{
	Entity * entity = new Client();

	entity->template_method(); 
	
	delete entity;
}