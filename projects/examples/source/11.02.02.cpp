#include <cassert>
#include <iostream>
#include <variant>

//////////////////////////////////////////////////////////////////////////////

class Client { public: void test() const { std::cout << "Client::test\n"; } };

class Server { public: void test() const { std::cout << "Server::test\n"; } };

//////////////////////////////////////////////////////////////////////////////

using Entity = std::variant < Client, Server > ;

//////////////////////////////////////////////////////////////////////////////

class Visitor_v1
{
public:

    void operator()(const Client & client) const { client.test(); }

    void operator()(const Server & server) const { server.test(); }
};

//////////////////////////////////////////////////////////////////////////////

template < typename ... Bs > class Visitor_v2 : public Bs ... 
{ 
public:

    using Bs::operator()...;
};

//////////////////////////////////////////////////////////////////////////////

int main()
{ 
    std::visit(             Visitor_v1   (), Entity(Client()));

    std::visit(Visitor_v2 < Visitor_v1 > (), Entity(Client()));
}