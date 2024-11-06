#include <iostream>

//  ================================================================================================

struct Client
{
    void test_v1() const { std::clog << "Client::test_v1\n"; }
    void test_v2() const { std::clog << "Client::test_v2\n"; }
};

//  ================================================================================================

struct Server
{
    void test_v1() const { std::clog << "Server::test_v1\n"; }
    void test_v2() const { std::clog << "Server::test_v2\n"; }
};

//  ================================================================================================

class Facade 
{
public:

    explicit Facade
    (
        Client & client, 
        Server & server
    )
    : 
        m_client(client), 
        m_server(server) 
    {}

//  ------------------------------------------------

    void test_v1() const
    {
        m_client.test_v1();
        m_server.test_v1();
    }

    void test_v2() const
    {
        m_client.test_v2();
        m_server.test_v2();
    }

private:

    Client & m_client;
    Server & m_server;
};

//  ================================================================================================

int main() 
{
    Client client;
    
    Server server;

    Facade facade(client, server);

    facade.test_v1();
    facade.test_v2();
}