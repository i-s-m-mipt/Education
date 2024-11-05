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

class Entity
{
public:

    explicit Entity(Strategy & strategy) : m_strategy(strategy) {}

//  ------------------------------------------------------------------------------------------------

    void test() const
    { 
        m_strategy.test(); 
    }

private:
    
    Strategy & m_strategy;
};

//  ================================================================================================

int main()
{
    Strategy * strategy = new Fast();

    Entity entity(*strategy);
    
    entity.test();

    delete strategy;
}