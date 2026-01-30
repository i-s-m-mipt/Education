////////////////////////////////////////////////////

// chapter : Software Architecture Patterns

////////////////////////////////////////////////////

// section : Structural Patterns

////////////////////////////////////////////////////

// content : Pattern Decorator

////////////////////////////////////////////////////

#include <print>

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
        std::print("Client::test\n");
    } 
};

////////////////////////////////////////////////////

class Server : public Entity 
{ 
public : 
    
    void test() const override 
    { 
        std::print("Server::test\n");
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
        std::print("Decorator::test : ");
        
        m_entity.test();
    }

private :

    Entity & m_entity;
};

////////////////////////////////////////////////////

int main()
{
    Entity * entity_1 = new Client;

    Entity * entity_2 = new Decorator(*entity_1);

//  ---------------------------------------------

    entity_2->test();

//  ---------------------------------------------

    delete entity_2;
     
    delete entity_1;
}

////////////////////////////////////////////////////