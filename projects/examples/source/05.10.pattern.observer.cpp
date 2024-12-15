#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////////

class Observer 
{
public:

    virtual ~Observer() = default; 

//  --------------------------------------

    virtual void test(int data) const = 0;
};

//////////////////////////////////////////////////////////////

class Entity 
{
public:

   ~Entity()
    {
        for (auto observer : m_observers) 
        {
            if (observer)
            {
                delete observer;
            }
        }
    }

//  -------------------------------------------------------

    void add_observer(Observer * observer) 
    { 
        m_observers.push_back(observer); 
    }

    void update_data(int data) 
    { 
        m_data = data; notify_observers();
    }

    void notify_observers() const
    { 
        for (auto observer : m_observers)
        {
            if (observer) 
            {
                observer->test(m_data);
            }
        }
    }

private:

    int m_data = 0; std::vector < Observer * > m_observers;
};

//////////////////////////////////////////////////////////////

class Client : public Observer 
{
public:

    void test(int data) const override
    {
        std::cout << "Client::test : data = " << data << '\n';
    }
};

//////////////////////////////////////////////////////////////

class Server : public Observer
{
public:

    void test(int data) const override
    {
        std::cout << "Server::test : data = " << data << '\n';
    }
};

//////////////////////////////////////////////////////////////

int main() 
{
    Entity entity;

    entity.add_observer(new Client()); entity.update_data(1);
    entity.add_observer(new Server()); entity.update_data(2);    
}