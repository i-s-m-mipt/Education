///////////////////////////////////////////////////////////////////////////////

// chapter : Software Engineering Patterns

///////////////////////////////////////////////////////////////////////////////

// content : Pattern Facade
//
// content : Variadic Base Classes

///////////////////////////////////////////////////////////////////////////////

// support : https://github.com/tdlib/td/blob/master/example/cpp/td_example.cpp

///////////////////////////////////////////////////////////////////////////////

#include <print>
#include <utility>

///////////////////////////////////////////////////////////////////////////////

class Client
{
public :

    Client(int) {}

//  ---------------------------------------------------------

    void test_v1() const { std::print("Client::test_v1\n"); }

    void test_v2() const { std::print("Client::test_v2\n"); }
};

///////////////////////////////////////////////////////////////////////////////

class Server
{
public :

    Server(int) {}

//  ---------------------------------------------------------

    void test_v1() const { std::print("Server::test_v1\n"); }

    void test_v2() const { std::print("Server::test_v2\n"); }
};

///////////////////////////////////////////////////////////////////////////////

template < typename ... Bs > class Facade : public Bs ...
{
public :

    template
    <
        typename ... Ts
    >
    Facade(int x, Ts && ... xs) : Bs(std::forward < Ts > (xs))..., m_x(x) {}

//  ------------------------------------------------------------------------

    void test_v1() const { (Bs::test_v1(), ...); }

    void test_v2() const { (Bs::test_v2(), ...); }

private :

    int m_x = 0;
};

///////////////////////////////////////////////////////////////////////////////

int main()
{
    Facade < Client, Server > facade(1, 1, 1);

//  ------------------------------------------

    facade.test_v1();

    facade.test_v2();
}

///////////////////////////////////////////////////////////////////////////////