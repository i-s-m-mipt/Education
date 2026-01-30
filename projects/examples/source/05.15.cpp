/////////////////////////////////////////////////////////

// chapter : Software Architecture Patterns

/////////////////////////////////////////////////////////

// section : Behavioral Patterns

/////////////////////////////////////////////////////////

// content : Pattern Strategy
//
// content : Policy-Based Programming

/////////////////////////////////////////////////////////

#include <print>

/////////////////////////////////////////////////////////

class Strategy 
{
public :

    virtual ~Strategy() = default;

//  ------------------------------

    virtual void test() const = 0;
};

/////////////////////////////////////////////////////////

class Client : public Strategy
{
public :

    void test() const override
    {
        std::print("Client::test\n");
    }
};

/////////////////////////////////////////////////////////

class Server : public Strategy
{
public :

    void test() const override
    {
        std::print("Server::test\n");
    }
};

/////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(Strategy & strategy) : m_strategy(strategy) {}

//  -----------------------------------------------------

    void test() const
    {
        m_strategy.test();
    }

private :

    Strategy & m_strategy;
};

/////////////////////////////////////////////////////////

int main()
{
    Strategy * strategy = new Client;

//  ---------------------------------

    Entity entity(*strategy);

//  ---------------------------------

    entity.test();

//  ---------------------------------

    delete strategy;
}

/////////////////////////////////////////////////////////