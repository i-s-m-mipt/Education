//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <latch>
#include <syncstream>
#include <thread>

//////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int x) : m_stream(std::cout), m_latch_1(x), m_latch_2(1) {}

//  ------------------------------------------------------------------

    auto & latch_1() const { return m_latch_1; }

    auto & latch_2() const { return m_latch_2; }

//  ------------------------------------------------------------------

    void execute(int x) const
    {
        test(x); m_latch_1.count_down();

        test(x); m_latch_2.wait();

        test(x);
    }

private :

    void test(int x) const
    {
        m_stream << "Entity::test : x = " << x << '\n';
    }

//  ------------------------------------------------------------------

    mutable std::osyncstream m_stream;

//  ------------------------------------------------------------------

    mutable std::latch m_latch_1;

    mutable std::latch m_latch_2;
};

//////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity(2);

//  ----------------------------------------------------

    std::jthread thread_1(&Entity::execute, &entity, 1);

    std::jthread thread_2(&Entity::execute, &entity, 2);

//  ----------------------------------------------------

    entity.latch_1().wait();

    entity.latch_2().count_down();
}

//////////////////////////////////////////////////////////////////////