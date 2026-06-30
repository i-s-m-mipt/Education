////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

////////////////////////////////////////////////////////////////////////////////////

// content : Thread Launch Synchronization
//
// content : Context Switches
//
// content : Function std::this_thread::yield

////////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <chrono>
#include <format>
#include <iostream>
#include <syncstream>
#include <thread>

////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    void test() const
    {
        trace();

        while (!m_flag)
        {
            std::this_thread::yield();
        }

        trace();
    }

//  --------------------------------------------------------------------------------

    void release()
    {
        m_flag = true;
    }

private :

    void trace() const
    {
        auto id = std::this_thread::get_id();

        std::osyncstream(std::cout) << std::format("Entity::trace : id = {}\n", id);
    }

//  --------------------------------------------------------------------------------

    std::atomic < bool > m_flag = false;
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