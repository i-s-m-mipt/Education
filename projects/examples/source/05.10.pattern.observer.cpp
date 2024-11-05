#include <iostream>
#include <string>
#include <vector>

//  ================================================================================================

struct Observer 
{
    virtual ~Observer() = default; 

    virtual void test(int data) const = 0;
};

//  ================================================================================================

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

//  ------------------------------------------------------------------------------------------------

    void set_data(int data) 
    { 
        m_data = data < 0 ? 0 : data; 
        
        notify_all();
    }

    void notify_all() const
    { 
        for (auto observer : m_observers)
        {
            if (observer) 
            {
                observer->test(m_data);
            }
        }
    }

    void add_observer(Observer * observer) 
    { 
        m_observers.push_back(observer); 
    }

private:

    int m_data = 0; std::vector < Observer * > m_observers;
};

//  ================================================================================================

struct Client : public Observer 
{
    void test(int data) const override
    {
        std::clog << "Client::test : data = " << data << '\n';
    }
};

//  ================================================================================================

struct Server : public Observer
{
    void test(int data) const override
    {
        std::clog << "Server::test : data = " << data << '\n';
    }
};

//  ================================================================================================

int main() 
{
    Entity entity;

    entity.add_observer(new Client()); entity.set_data(1);
    entity.add_observer(new Server()); entity.set_data(2);    
}