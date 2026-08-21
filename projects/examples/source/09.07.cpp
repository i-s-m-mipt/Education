///////////////////////////////////////////////////////////////////////////

// chapter : Distributed Network Systems

///////////////////////////////////////////////////////////////////////////

// content : Pattern Mediator

///////////////////////////////////////////////////////////////////////////

#include <memory>
#include <print>
#include <vector>

///////////////////////////////////////////////////////////////////////////

class Mediator;

///////////////////////////////////////////////////////////////////////////

class Client : public std::enable_shared_from_this < Client >
{
public :

    Client(std::shared_ptr < Mediator > mediator) : m_mediator(mediator) {}

//  -----------------------------------------------------------------------

    void send(int x);

//  -----------------------------------------------------------------------

    void receive(int x) const
    {
        std::print("Client::receive : x = {}\n", x);
    }

private:

    std::weak_ptr < Mediator > m_mediator;
};

///////////////////////////////////////////////////////////////////////////

class Mediator
{
public :

    auto const & clients() const
    {
        return m_clients;
    }

//  ---------------------------------------------------------

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

///////////////////////////////////////////////////////////////////////////

void Client::send(int x)
{
    m_mediator.lock()->send(shared_from_this(), x);
}

///////////////////////////////////////////////////////////////////////////

int main()
{
    auto mediator = std::make_shared < Mediator > ();

//  ----------------------------------------------------------

    for (auto i = 0uz; i < 3; ++i)
    {
        mediator->add(std::make_shared < Client > (mediator));
    }

//  ----------------------------------------------------------

    mediator->clients().front()->send(1);
}

///////////////////////////////////////////////////////////////////////////