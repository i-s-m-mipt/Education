#include <cassert>
#include <iostream>
#include <variant>

///////////////////////////////////////////////////////////////////////////////

class Client { public: void test() const { std::cout << "Client::test\n"; } };

class Server { public: void test() const { std::cout << "Server::test\n"; } };

///////////////////////////////////////////////////////////////////////////////

using Entity = std::variant < Client, Server > ;

///////////////////////////////////////////////////////////////////////////////

class Router
{
public:

    void operator()(const Client & client) const { client.test(); }

    void operator()(const Server & server) const { server.test(); }
};

///////////////////////////////////////////////////////////////////////////////

template < typename ... Bs > class Visitor : public Bs ... 
{ 
public:

    using Bs::operator()...;
};

///////////////////////////////////////////////////////////////////////////////

int main()
{
    {   
        std::visit(Visitor < Router > (), Entity(Client()));
    }
    
//  --------------------------------------------------------

    {
        auto lambda = [](auto x){ return x; };

        Visitor < decltype(lambda) > visitor(lambda);

        std::variant < int > variant = 1;

        assert(std::visit(visitor, variant) == 1);
    }
}