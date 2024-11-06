#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <variant>

//  ================================================================================================

struct Client { void test() const { std::clog << "Client::test\n"; }; };
struct Server { void test() const { std::clog << "Server::test\n"; }; };

//  ================================================================================================

using System = std::variant < Client, Server > ;

//  ================================================================================================

struct Router
{
    void operator()(const Client & client) const { client.test(); }
    void operator()(const Server & server) const { server.test(); }
};

//  ================================================================================================

template < typename ... Bs > struct Visitor : public Bs ... 
{ 
    using Bs::operator()...; 
};

//  ================================================================================================

int main()
{
    System system_1 = Client();
    System system_2 = Server();

    Visitor < Router > visitor;
   
    std::visit(visitor, system_1);
    std::visit(visitor, system_2);

//  ------------------------------------------------------------------------------------------------

    auto lambda = [](auto x){ return x; };

    Visitor < decltype(lambda) > handle(lambda);

    assert(std::visit(lambda, std::variant < int > (1)) == 1);
    assert(std::visit(handle, std::variant < int > (1)) == 1);
}