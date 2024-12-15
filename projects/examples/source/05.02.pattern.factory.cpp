#include <iostream>

///////////////////////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default;

//  ------------------------------

    virtual void test() const = 0;
};

///////////////////////////////////////////////////////////

class Client : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Client::test\n"; 
    } 
};

///////////////////////////////////////////////////////////

class Server : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Server::test\n"; 
    } 
};

///////////////////////////////////////////////////////////

template < typename E > auto make_entity() -> Entity *
{ 
    return new E(); 
}

///////////////////////////////////////////////////////////

class Router : public Entity
{
public:

    class Factory
    {
    public:

        static auto make_v1() -> Entity * { return new Router(1); }
        static auto make_v2() -> Entity * { return new Router(2); }
    };

//  -------------------------------------------------------

    void test() const override 
    { 
        std::cout << "Router::test\n"; 
    };

private:

    explicit Router(int data) : m_data(data) {};

//  -------------------------------------------------------

    int m_data = 0;
};

///////////////////////////////////////////////////////////

struct Factory
{
    virtual ~Factory() = default; 

    virtual Entity * make() const = 0;  
};

///////////////////////////////////////////////////////////

class Factory_Client : public Factory 
{ 
public: 
    
    Entity * make() const override 
    { 
        return new Client(); 
    } 
};

///////////////////////////////////////////////////////////

class Factory_Server : public Factory 
{ 
public: 
    
    Entity * make() const override 
    { 
        return new Server(); 
    } 
};

///////////////////////////////////////////////////////////

int main()
{
    auto entity_v1 = make_entity < Client > (); 

    entity_v1->test(); 
    
    delete entity_v1;

//  --------------------------------------------

    auto entity_v2 = Router::Factory::make_v1(); 

    entity_v2->test(); 
    
    delete entity_v2;

//  --------------------------------------------

    Factory * factory = new Factory_Server();

    auto entity_v3 = factory->make(); 

    entity_v3->test(); 
    
    delete entity_v3; delete factory;
}