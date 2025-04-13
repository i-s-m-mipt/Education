////////////////////////////////////////////////////

#include <iostream>

////////////////////////////////////////////////////

class Entity 
{
public :

    virtual ~Entity() = default;

//  ------------------------------

    virtual void test() const = 0;
};

////////////////////////////////////////////////////

class Client : public Entity 
{ 
public : 
    
    void test() const override 
    { 
        std::cout << "Client::test\n";
    } 
};

////////////////////////////////////////////////////

class Server : public Entity 
{ 
public : 
    
    void test() const override 
    { 
        std::cout << "Server::test\n";
    } 
};

////////////////////////////////////////////////////

class Decorator : public Entity
{
public :

    Decorator(Entity & entity) : m_entity(entity) {}

//  ------------------------------------------------

    void test() const override
    { 
        std::cout << "Decorator::test : ";

    //  ----------------------------------
        
        m_entity.test();
    }

private :

    Entity & m_entity;
};

////////////////////////////////////////////////////

int main()
{
    Entity * entity_1 = new Client;

//  ---------------------------------------------

    Entity * entity_2 = new Decorator(*entity_1);

//  ---------------------------------------------

    entity_1->test();

    entity_2->test();

//  ---------------------------------------------

    delete entity_2;
     
    delete entity_1;
}

////////////////////////////////////////////////////