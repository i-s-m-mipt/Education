/////////////////////////////////////////////

// chapter : Software Engineering Patterns

/////////////////////////////////////////////

// content : Pattern Factory

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

class Factory_v1 : public Factory
{
public :

    Entity * make_entity() const override
    {
        return new Client;
    }
};

/////////////////////////////////////////////

class Factory_v2 : public Factory
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
    Factory * factory = new Factory_v1;

//  -----------------------------------

    delete factory->make_entity();

    delete factory;
}

/////////////////////////////////////////////