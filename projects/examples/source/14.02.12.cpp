////////////////////////////////////////////////////////

#include <chrono>
#include <iostream>
#include <latch>
#include <syncstream>
#include <thread>

////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_latch(1) {}

//  ----------------------------------------------------

    void test() const
    {
        trace(); m_latch.wait();

        trace(); 
    }

//  ----------------------------------------------------

    void release() const
    {
        m_latch.count_down();
    }

private :

    void trace() const
    {
        std::osyncstream stream(std::cout);

        auto id = std::this_thread::get_id();

        stream << "Entity::trace : id = " << id << '\n';
    }

//  ----------------------------------------------------

    mutable std::latch m_latch;
};

////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  ----------------------------------------------

    std::jthread thread_1(&Entity::test, &entity);

    std::jthread thread_2(&Entity::test, &entity);

//  ----------------------------------------------

    std::this_thread::sleep_for(1s);

//  ----------------------------------------------

    entity.release();
}

////////////////////////////////////////////////////////