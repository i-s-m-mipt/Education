#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <variant>

//  ================================================================================================

class Client { public: void test() const { std::clog << "Client::test\n"; }; };
class Server { public: void test() const { std::clog << "Server::test\n"; }; };

//  ================================================================================================

using Entity = std::variant < Client, Server > ;

//  ================================================================================================

class Router
{
public:

    void operator()(const Client & client) const { client.test(); }
    void operator()(const Server & server) const { server.test(); }
};

//  ================================================================================================

template < typename ... Bs > class Visitor : public Bs ... 
{ 
public:

    using Bs::operator()...; 
};

//  ================================================================================================

int main()
{
    Entity entity_1 = Client();
    Entity entity_2 = Server();

    Visitor < Router > visitor;
   
    std::visit(visitor, entity_1);
    std::visit(visitor, entity_2);

//  --------------------------------------

    auto lambda = [](auto x){ return x; };

    Visitor < decltype(lambda) > handle(lambda);

    assert(std::visit(lambda, std::variant < int > (1)) == 1);
    assert(std::visit(handle, std::variant < int > (1)) == 1);
}