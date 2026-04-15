////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

////////////////////////////////////////////////////////////////////////////////////

// section : Synchronization

////////////////////////////////////////////////////////////////////////////////////

// content : Thread Launch Synchronization
//
// content : Semaphores
//
// content : Primitive std::counting_semaphore

////////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <format>
#include <iostream>
#include <semaphore>
#include <syncstream>
#include <thread>

////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_semaphore(0) {}

//  --------------------------------------------------------------------------------

    void test() const
    {
        trace(); m_semaphore.acquire();

        trace(); m_semaphore.release();
    }

//  --------------------------------------------------------------------------------

    void release() const
    {   
        m_semaphore.release(m_semaphore.max());
    }

private :

    void trace() const
    {
        auto id = std::this_thread::get_id();

        std::osyncstream(std::cout) << std::format("Entity::trace : id = {}\n", id);
    }

//  --------------------------------------------------------------------------------

    mutable std::counting_semaphore < 2 > m_semaphore;
};

////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////