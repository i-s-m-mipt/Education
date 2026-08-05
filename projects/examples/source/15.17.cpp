///////////////////////////////////////////////////////////////////

// chapter : Distributed Network Systems

///////////////////////////////////////////////////////////////////

// content : Pattern Mediator

///////////////////////////////////////////////////////////////////

#include <memory>
#include <print>
#include <vector>

///////////////////////////////////////////////////////////////////

class Server;

///////////////////////////////////////////////////////////////////

class Client : public std::enable_shared_from_this < Client >
{
public :

    Client(std::shared_ptr < Server > server) : m_server(server) {}

//  ---------------------------------------------------------------

    void send(int x);

//  ---------------------------------------------------------------

    void receive(int x) const
    {
        std::print("Client::receive : x = {}\n", x);
    }

private:

    std::weak_ptr < Server > m_server;
};

///////////////////////////////////////////////////////////////////

class Server
{
public :

    void add(std::shared_ptr < Client > client)
    {
        m_clients.push_back(client);
    }

//  ---------------------------------------------------------

    void send(std::shared_ptr < Client > sender, int x) const
    {
        for (auto const & client : m_clients)
        {
            if (client != sender)
            {
                client->receive(x);
            }
        }
    }

private :

    std::vector < std::shared_ptr < Client > > m_clients;
};

///////////////////////////////////////////////////////////////////

void Client::send(int x)
{
    m_server.lock()->send(shared_from_this(), x);
}

///////////////////////////////////////////////////////////////////

int main()
{
    auto server = std::make_shared < Server > ();

    auto client = std::make_shared < Client > (server);

//  ------------------------------------------------------

    server->add(client);

//  ------------------------------------------------------

    for (auto i = 0uz; i < 2; ++i)
    {
        server->add(std::make_shared < Client > (server));
    }

//  ------------------------------------------------------

    client->send(1);
}

///////////////////////////////////////////////////////////////////