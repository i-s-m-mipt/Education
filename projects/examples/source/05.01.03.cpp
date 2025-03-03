#include <iostream>

///////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default;
};

///////////////////////////////////////////

class Client : public Entity {};

class Server : public Entity {};

///////////////////////////////////////////

class Factory
{
public:

    virtual ~Factory() = default;

//  ----------------------------------

    virtual Entity * make() const = 0;
};

///////////////////////////////////////////

class Factory_Client : public Factory 
{ 
public: 
    
    Entity * make() const override 
    { 
        return new Client;
    } 
};

///////////////////////////////////////////

class Factory_Server : public Factory 
{ 
public: 
    
    Entity * make() const override 
    { 
        return new Server;
    } 
};

///////////////////////////////////////////

int main()
{
    Factory * factory = new Factory_Client;

//  ---------------------------------------

    delete factory->make();
        
    delete factory;
}