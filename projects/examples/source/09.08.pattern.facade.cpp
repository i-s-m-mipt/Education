#include <iostream>

//////////////////////////////////////////////////////////////

class Client
{
public:

    void test_v1() const { std::clog << "Client::test_v1\n"; }
    void test_v2() const { std::clog << "Client::test_v2\n"; }
};

//////////////////////////////////////////////////////////////

class Server
{
public:

    void test_v1() const { std::clog << "Server::test_v1\n"; }
    void test_v2() const { std::clog << "Server::test_v2\n"; }
};

//////////////////////////////////////////////////////////////

class Facade : private Client, private Server
{
public:

    void test_v1() const
    {
        Client::test_v1();
        Server::test_v1();
    }

    void test_v2() const
    {
        Client::test_v2();
        Server::test_v2();
    }
};

//////////////////////////////////////////////////////////////

int main() 
{
    Facade facade;

    facade.test_v1();
    facade.test_v2();
}