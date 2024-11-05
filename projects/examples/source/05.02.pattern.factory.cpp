#include <iostream>
#include <string>

//  ================================================================================================

struct Entity
{
    virtual ~Entity() = default;

    virtual void test() const = 0;
};

//  ================================================================================================

struct Client : public Entity { void test() const override { std::clog << "Client::test\n"; } };
struct Server : public Entity { void test() const override { std::clog << "Server::test\n"; } };

//  ================================================================================================

template < typename E > [[nodiscard]] Entity * make_entity()
{ 
    return new E(); 
}

//  ================================================================================================

class Router : public Entity
{
public:

    struct Factory
    {
        [[nodiscard]] static Entity * make_v1() { return new Router(1); }
        [[nodiscard]] static Entity * make_v2() { return new Router(2); }
    };

//  ------------------------------------------------------------------------------------------------

    void test() const override 
    { 
        std::clog << "Router::test\n"; 
    };

private:

    explicit Router(int data) : m_data(data) {};

//  ------------------------------------------------------------------------------------------------

    int m_data = 0;
};

//  ================================================================================================

struct Factory
{
    virtual ~Factory() = default; 

    [[nodiscard]] virtual Entity * make() const = 0;  
};

//  ================================================================================================

struct Factory_Client : public Factory
{
    [[nodiscard]] Entity * make() const override 
    { 
        return new Client(); 
    } 
};

//  ================================================================================================

struct Factory_Server : public Factory
{
    [[nodiscard]] Entity * make() const override 
    { 
        return new Server(); 
    }
};

//  ================================================================================================

int main()
{
    auto entity_v1 = make_entity < Client > (); 

    entity_v1->test(); 
    
    delete entity_v1;

//  ------------------------------------------------------------------------------------------------

    auto entity_v2 = Router::Factory::make_v1(); 

    entity_v2->test(); 
    
    delete entity_v2;

//  ------------------------------------------------------------------------------------------------

    Factory * factory = new Factory_Server();

    auto entity_v3 = factory->make(); 

    entity_v3->test(); 
    
    delete entity_v3; delete factory;
}