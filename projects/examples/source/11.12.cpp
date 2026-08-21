///////////////////////////////////////////////////////////////////////

// chapter : Programming with Algorithms

///////////////////////////////////////////////////////////////////////

// content : Pattern Visitor
//
// content : Double Dispatching

///////////////////////////////////////////////////////////////////////

#include <memory>
#include <print>

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
        std::print("Client::test\n");
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
        std::print("Server::test\n");
    }

//  ---------------------------------------------------

    void invoke(Visitor const & visitor) const override
    {
        visitor.visit(this);
    }
};

///////////////////////////////////////////////////////////////////////

class Visitor_v1 : public Visitor
{
public :

    void visit([[maybe_unused]] Client const * client) const override
    {
        std::print("Visitor_v1::visit (1)\n");

        client->test();
    }

//  -----------------------------------------------------------------

    void visit([[maybe_unused]] Server const * server) const override
    {
        std::print("Visitor_v1::visit (2)\n");
    }
};

///////////////////////////////////////////////////////////////////////

class Visitor_v2 : public Visitor
{
public :

    void visit([[maybe_unused]] Client const * client) const override
    {
        std::print("Visitor_v2::visit (1)\n");
    }

//  -----------------------------------------------------------------

    void visit([[maybe_unused]] Server const * server) const override
    {
        std::print("Visitor_v2::visit (2)\n");

        server->test();
    }
};

///////////////////////////////////////////////////////////////////////

int main()
{
    std::shared_ptr < Entity > entity = std::make_shared < Client > ();

//  -------------------------------------------------------------------

    Visitor_v1 visitor_v1;

//  -------------------------------------------------------------------

    entity->invoke(visitor_v1);
}

///////////////////////////////////////////////////////////////////////