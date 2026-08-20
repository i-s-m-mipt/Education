/////////////////////////////////////////////////////////

// chapter : Software Engineering Patterns

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

class Strategy_v1 : public Strategy
{
public :

    void test() const override
    {
        std::print("Strategy_v1::test\n");
    }
};

/////////////////////////////////////////////////////////

class Strategy_v2 : public Strategy
{
public :

    void test() const override
    {
        std::print("Strategy_v2::test\n");
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
    Strategy * strategy = new Strategy_v1;

//  --------------------------------------

    Entity entity(*strategy);

//  --------------------------------------

    entity.test();

//  --------------------------------------

    delete strategy;
}

/////////////////////////////////////////////////////////