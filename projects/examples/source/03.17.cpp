/////////////////////////////////////////////

#include <iostream>
#include <vector>

/////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  -----------------------------------------

    virtual void test_v1() const = 0;

//  -----------------------------------------

//	virtual void test_v2() const = 0 // error
//	{
//		std::cout << "Entity::test_v2\n";
//	}
};

/////////////////////////////////////////////

void Entity::test_v1() const
{ 
	std::cout << "Entity::test_v1\n";
}

/////////////////////////////////////////////

class Client : public Entity
{
public :

    void test_v1() const override 
	{ 
		std::cout << "Client::test_v1\n";
		
		Entity::test_v1();
	}
};

/////////////////////////////////////////////

int main()
{
    std::vector < Entity * > entities;

//  ----------------------------------------

//  entities.push_back(new Entity); // error

    entities.push_back(new Client);

//  ----------------------------------------

    for (auto entity : entities)
    {
        entity->test_v1();
    }

//  ----------------------------------------

    for (auto entity : entities)
    {
        delete entity;
    }
}

/////////////////////////////////////////////