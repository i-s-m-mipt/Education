//////////////////////////////////////////////////////

// chapter : Software Engineering Patterns

//////////////////////////////////////////////////////

// content : Pattern Observer
//
// content : Condition Variables

//////////////////////////////////////////////////////

#include <print>
#include <vector>

//////////////////////////////////////////////////////

class Observer
{
public :

    virtual ~Observer() = default;

//  -----------------------------------

    virtual void test(int x) const = 0;
};

//////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////

class Observer_v1 : public Observer
{
public :

    void test(int x) const override
    {
        std::print("Observer_v1::test : x = {}\n", x);
    }
};

//////////////////////////////////////////////////////

class Observer_v2 : public Observer
{
public :

    void test(int x) const override
    {
        std::print("Observer_v2::test : x = {}\n", x);
    }
};

//////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  ----------------------------

    entity.add(new Observer_v1);

    entity.add(new Observer_v2);

//  ----------------------------

    for (auto i = 1; i < 3; ++i)
    {
        entity.set(i);
    }
}

//////////////////////////////////////////////////////