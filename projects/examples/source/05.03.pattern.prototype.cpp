#include <iostream>

///////////////////////////////////////////////////////////////////////////////////

class Entity
{    
public:

    virtual ~Entity() = default; 

//  ----------------------------------

    virtual Entity * copy() const = 0;

    virtual void     test() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////

class Client : public Entity
{
public:

    Entity * copy() const override 
    { 
        return new Client(*this); 
    } 

    void test() const override 
    { 
        std::cout << "Client::test\n"; 
    };
};

///////////////////////////////////////////////////////////////////////////////////

class Server : public Entity
{
public:

    Entity * copy() const override 
    { 
        return new Server(*this); 
    } 

    void test() const override 
    { 
        std::cout << "Server::test\n"; 
    };
};

///////////////////////////////////////////////////////////////////////////////////

class Factory
{
public:

    static auto make_client() { static Client prototype; return prototype.copy(); }
    
    static auto make_server() { static Server prototype; return prototype.copy(); }
};

///////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto entity = Factory::make_client(); 

    entity->test(); 
    
    delete entity;
}