////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

////////////////////////////////////////////////////////

class Observer 
{
public :

    virtual ~Observer() = default;

//  -----------------------------------

    virtual void test(int x) const = 0;
};

////////////////////////////////////////////////////////

class Entity 
{
public :

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

//  ---------------------------------------

    void add_observer(Observer * observer)
    { 
        m_observers.push_back(observer);
    }

//  ---------------------------------------

    void set(int x) 
    { 
        m_x = x;

    //  -------------------
        
        notify_observers();
    }

//  ---------------------------------------

    void notify_observers() const
    { 
        for (auto observer : m_observers)
        {
            if (observer) 
            {
                observer->test(m_x);
            }
        }
    }

private :

    int m_x = 0;

//  ---------------------------------------
    
    std::vector < Observer * > m_observers;
};

////////////////////////////////////////////////////////

class Client : public Observer 
{
public :

    void test(int x) const override
    {
        std::cout << "Client::test : x = " << x << '\n';
    }
};

////////////////////////////////////////////////////////

class Server : public Observer
{
public :

    void test(int x) const override
    {
        std::cout << "Server::test : x = " << x << '\n';
    }
};

////////////////////////////////////////////////////////

int main() 
{
    Entity entity;

//  --------------------------------

    entity.add_observer(new Client);
    
    entity.add_observer(new Server);

//  --------------------------------
    
    for (auto i = 0; i < 2; ++i)
    {
        entity.set(i + 1);
    }
}

////////////////////////////////////////////////////////