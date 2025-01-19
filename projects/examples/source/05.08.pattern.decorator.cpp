#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Entity 
{
public:

    virtual ~Entity() = default; 

//  ------------------------------

    virtual void test() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Client::test\n"; 
    } 
};

////////////////////////////////////////////////////////////

class Server : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Server::test\n"; 
    } 
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Decorator : public Entity
{
public:

    Decorator(Entity & entity): m_entity(entity) {}

protected:

    Entity & m_entity;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Decorated_Entity : public Decorator
{
public:

    Decorated_Entity(Entity & entity) : Decorator(entity) {}

//  -----------------------------------------------------------------

    void test() const override
    { 
        std::cout << "Decorated_Entity::test : "; 
        
        m_entity.test();
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity * entity_1 = new Client;

    Entity * entity_2 = new Decorated_Entity(*entity_1);

    entity_1->test();

    entity_2->test(); 
     
    delete entity_1;  
     
    delete entity_2; 
}