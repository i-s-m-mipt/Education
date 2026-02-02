/////////////////////////////////////////////

// chapter : Software Design Patterns

/////////////////////////////////////////////

// section : Generative Patterns

/////////////////////////////////////////////

// content : Pattern Abstract Factory

/////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;
};

/////////////////////////////////////////////

class Client : public Entity {};

class Server : public Entity {};

/////////////////////////////////////////////

class Factory
{
public :

    virtual ~Factory() = default;

//  -----------------------------------------

    virtual Entity * make_entity() const = 0;
};

/////////////////////////////////////////////

class Factory_Client : public Factory 
{ 
public : 
    
    Entity * make_entity() const override 
    { 
        return new Client;
    } 
};

/////////////////////////////////////////////

class Factory_Server : public Factory 
{ 
public : 
    
    Entity * make_entity() const override 
    { 
        return new Server;
    } 
};

/////////////////////////////////////////////

int main()
{
    Factory * factory = new Factory_Client;

//  ---------------------------------------

    delete factory->make_entity();
        
    delete factory;
}

/////////////////////////////////////////////