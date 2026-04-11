////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

////////////////////////////////////////////////////////////////////////////////////

// section : Synchronization

////////////////////////////////////////////////////////////////////////////////////

// content : Thread Launch Synchronization
//
// content : Latches
//
// content : Primitive std::latch

////////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <format>
#include <iostream>
#include <latch>
#include <syncstream>
#include <thread>

////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_latch(1) {}

//  --------------------------------------------------------------------------------

    void test() const
    {
        trace(); m_latch.wait();

        trace(); 
    }

//  --------------------------------------------------------------------------------

    void release() const
    {
        m_latch.count_down();
    }

private :

    void trace() const
    {
        auto id = std::this_thread::get_id();

        std::osyncstream(std::cout) << std::format("Entity::trace : id = {}\n", id);
    }

//  --------------------------------------------------------------------------------

    mutable std::latch m_latch;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -----------------------------------------------

    std::jthread jthread_1(&Entity::test, &entity);

    std::jthread jthread_2(&Entity::test, &entity);

//  -----------------------------------------------

    std::this_thread::sleep_for(1s);

//  -----------------------------------------------

    entity.release();
}

////////////////////////////////////////////////////////////////////////////////////