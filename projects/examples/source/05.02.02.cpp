//////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////

class Entity_v1
{
public :

    virtual ~Entity_v1() = default;

//  -------------------------------

    virtual void test() const = 0;
};

//////////////////////////////////////////////////////////////

class Client_v1 : public Entity_v1 
{ 
public :

    void test() const override 
    { 
        std::cout << "Client_v1::test\n";
    } 
};

//////////////////////////////////////////////////////////////

class Client_v2 : public Entity_v1 
{ 
public : 

    void test() const override 
    { 
        std::cout << "Client_v2::test\n";
    } 
};

//////////////////////////////////////////////////////////////

class Entity_v2
{
public :

    Entity_v2(Entity_v1 & entity_v1) : m_bridge(entity_v1) {}

//  ---------------------------------------------------------

    virtual ~Entity_v2() = default;

//  ---------------------------------------------------------

    virtual void test() const = 0;

protected :

    Entity_v1 & m_bridge;
};

//////////////////////////////////////////////////////////////

class Server_v1 : public Entity_v2 
{
public :

    Server_v1(Entity_v1 & entity_v1) : Entity_v2(entity_v1) {}

//  ----------------------------------------------------------

    void test() const override 
    {
        std::cout << "Server_v1::test\n";

        m_bridge.test();
    }
};

//////////////////////////////////////////////////////////////

class Server_v2 : public Entity_v2 
{
public :

    Server_v2(Entity_v1 & entity_v1) : Entity_v2(entity_v1) {}

//  ----------------------------------------------------------

    void test() const override 
    { 
        std::cout << "Server_v2::test\n";

        m_bridge.test();
    }
};

//////////////////////////////////////////////////////////////

int main() 
{
    Entity_v1 * entity_v1 = new Client_v1;
    
    Entity_v2 * entity_v2 = new Server_v1(*entity_v1);

//  --------------------------------------------------

    entity_v2->test();

//  --------------------------------------------------

    delete entity_v2;
    
    delete entity_v1;
}

//////////////////////////////////////////////////////////////