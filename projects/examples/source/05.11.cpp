/////////////////////////////////////////////////////////////

// chapter : Software Design Patterns

/////////////////////////////////////////////////////////////

// section : Constructional Patterns

/////////////////////////////////////////////////////////////

// content : Pattern Facade

/////////////////////////////////////////////////////////////

#include <print>

/////////////////////////////////////////////////////////////

class Client
{
public :

    void test_v1() const { std::print("Client::test_v1\n"); }
    
    void test_v2() const { std::print("Client::test_v2\n"); }
};

/////////////////////////////////////////////////////////////

class Server
{
public :

    void test_v1() const { std::print("Server::test_v1\n"); }

    void test_v2() const { std::print("Server::test_v2\n"); }
};

/////////////////////////////////////////////////////////////

class Facade : private Client, private Server
{
public :

    void test_v1() const
    {
        Client::test_v1();

        Server::test_v1();
    }

//  ----------------------

    void test_v2() const
    {
        Client::test_v2();

        Server::test_v2();
    }
};

/////////////////////////////////////////////////////////////

int main() 
{
    Facade facade;

//  -----------------

    facade.test_v1();

    facade.test_v2();
}

/////////////////////////////////////////////////////////////