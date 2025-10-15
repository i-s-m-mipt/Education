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
            delete observer;
        }
    }

//  ---------------------------------------

    void add(Observer * observer)
    { 
        m_observers.push_back(observer);
    }

//  ---------------------------------------

    void set(int x) 
    { 
        m_x = x;
        
        notify_all();
    }

//  ---------------------------------------

    void notify_all() const
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

//  ----------------------------

    entity.add(new Client);
    
    entity.add(new Server);

//  ----------------------------
    
    for (auto i = 0; i < 2; ++i)
    {
        entity.set(i + 1);
    }
}

////////////////////////////////////////////////////////