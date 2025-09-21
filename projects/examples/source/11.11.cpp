///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>

///////////////////////////////////////////////////////////////////////

class Visitor
{
public :

    virtual ~Visitor() = default;

//  ----------------------------------------------------------

    virtual void visit(class Client const * client) const = 0;
    
    virtual void visit(class Server const * server) const = 0;
};

///////////////////////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  -------------------------------------------------------

    virtual void test() const = 0;

//  -------------------------------------------------------

    virtual void invoke(Visitor const & visitor) const = 0;
};

///////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public :

    void test() const override 
    { 
        std::cout << "Client::test\n";
    }

//  ---------------------------------------------------

    void invoke(Visitor const & visitor) const override
    { 
        visitor.visit(this);
    }
};

///////////////////////////////////////////////////////////////////////

class Server : public Entity
{
public :

    void test() const override 
    { 
        std::cout << "Server::test\n";
    }

//  ---------------------------------------------------

    void invoke(Visitor const & visitor) const override
    {
        visitor.visit(this);
    }
};

///////////////////////////////////////////////////////////////////////

class Router : public Visitor
{
public :

    void visit(Client const * client) const override 
    { 
        std::cout << "Router::visit (1)\n";

        client->test();
    }

//  ------------------------------------------------

    void visit(Server const * server) const override 
    {
        std::cout << "Router::visit (2)\n";

        server->test();
    }
};

///////////////////////////////////////////////////////////////////////

int main()
{
    std::shared_ptr < Entity > entity = std::make_shared < Client > ();

//  -------------------------------------------------------------------

    Router router;

//  -------------------------------------------------------------------

    entity->invoke(router);
}

///////////////////////////////////////////////////////////////////////