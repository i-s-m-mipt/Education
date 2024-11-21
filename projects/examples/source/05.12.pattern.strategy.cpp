#include <iostream>

//  ================================================================================================

struct Strategy 
{
    virtual ~Strategy() = default; 

    virtual void test() const = 0;
};

//  ================================================================================================

struct Fast : public Strategy { void test() const override { std::clog << "Fast::test\n"; } };
struct Slow : public Strategy { void test() const override { std::clog << "Slow::test\n"; } };

//  ================================================================================================

class Entity_v1
{
public:

    explicit Entity_v1(Strategy & strategy) : m_strategy(strategy) {}

//  -----------------------------------------------------------------

    void test() const
    { 
        m_strategy.test(); 
    }

private:
    
    Strategy & m_strategy;
};

//  ===============================

struct Entity_v2 : private Strategy
{
    void test() const
    { 
        Strategy::test(); 
    }
};

//  ================================================================================================

int main()
{
    Strategy * strategy = new Fast();

    Entity_v1 entity_v1(*strategy);

    Entity_v2 entity_v2;
    
    entity_v1.test();
    entity_v2.test();

    delete strategy;
}