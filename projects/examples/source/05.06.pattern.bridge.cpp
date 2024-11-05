#include <iostream>

//  ================================================================================================

struct Entity_v1
{
    virtual ~Entity_v1() = default; 

    virtual void test() const = 0;
};

//  ================================================================================================

struct Client_v1 : public Entity_v1 { void test() const override { std::clog << "Client_v1::test\n"; } };
struct Client_v2 : public Entity_v1 { void test() const override { std::clog << "Client_v2::test\n"; } };

//  ================================================================================================

class Entity_v2
{
public:

    explicit Entity_v2(Entity_v1 & entity_v1) : m_entity_v1(entity_v1) {}

    virtual ~Entity_v2() = default; 

//  ------------------------------------------------------------------------------------------------

    virtual void test() const = 0;

protected:

    Entity_v1 & m_entity_v1;
};

//  ================================================================================================

struct Server_v1 : public Entity_v2 
{
    explicit Server_v1(Entity_v1 & entity_v1) : Entity_v2(entity_v1) {}

//  ------------------------------------------------------------------------------------------------

    void test() const override 
    {
        std::clog << "Server_v1::test\n";

        m_entity_v1.test(); 
    }
};

//  ================================================================================================

struct Server_v2 : public Entity_v2 
{
    explicit Server_v2(Entity_v1 & entity_v1) : Entity_v2(entity_v1) {}

//  ------------------------------------------------------------------------------------------------

    void test() const override 
    { 
        std::clog << "Server_v2::test\n";

        m_entity_v1.test(); 
    }
};

//  ================================================================================================

int main() 
{
    Entity_v1 * entity_v1 = new Client_v1();
    
    Entity_v2 * entity_v2 = new Server_v1(*entity_v1);

    entity_v2->test(); 
    
    delete entity_v1;
    delete entity_v2;
}