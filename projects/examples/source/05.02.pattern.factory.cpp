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

    Router(int data) : m_data(data) {};

//  -------------------------------------------------------

    int m_data = 0;
};

///////////////////////////////////////////////////////////

class Factory
{
public:

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
    {
        auto entity = make_entity < Client > (); 

        entity->test(); 
    
        delete entity;
    }
    
//  ---------------------------------------------

    {
        auto entity = Router::Factory::make_v1(); 

        entity->test(); 
    
        delete entity;
    }

//  ---------------------------------------------

    {
        Factory * factory = new Factory_Server();

        auto entity = factory->make(); 

        entity->test(); 
    
        delete entity; delete factory;
    }
}