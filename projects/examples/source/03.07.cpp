/////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

/////////////////////////////////////////////////////

// content : Class Relations
//
// content : Composition and Aggregation
//
// content : Association
//
// content : Forward Declarations
//
// content : Dependency
//
// content : Stream std::cout
//
// content : Operator <<

/////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <print>

/////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int x) : m_x(x) {}

//  ----------------------------------

    void test() const
    {
        std::cout << "Entity::test\n";
    }

//  ----------------------------------

    static inline auto s_x = 1;

private :

    int m_x = 0;
};

/////////////////////////////////////////////////////

class Server;

/////////////////////////////////////////////////////

class Client
{
public :

    void initialize(Server * server)
    {
        m_server = server;
    }

//  ------------------------------------

    void test_v1() const
    {
        std::print("Client::test_v1\n");
    }

//  ------------------------------------

    void test_v2() const;

private :

    Server * m_server = nullptr;
};

/////////////////////////////////////////////////////

class Server
{
public :

    void initialize(Client * client)
    {
        m_client = client;
    }

//  ------------------------------------

    void test_v1() const
    {
        std::print("Server::test_v1\n");
    }

//  ------------------------------------

    void test_v2() const;

private :

    Client * m_client = nullptr;
};

/////////////////////////////////////////////////////

void Client::test_v2() const { m_server->test_v1(); }

void Server::test_v2() const { m_client->test_v1(); }

/////////////////////////////////////////////////////

int main()
{
    Entity entity_1(1);

    Entity entity_2(2);

//  ---------------------------

    assert(Entity::s_x == 1);

//  ---------------------------

    Client client;

    Server server;

//  ---------------------------

    server.initialize(&client);

    client.initialize(&server);

//  ---------------------------

    client.test_v2();

    server.test_v2();

//  ---------------------------

    Entity(1).test();
}

/////////////////////////////////////////////////////