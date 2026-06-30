////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

////////////////////////////////////////////////////////////////////////////////////

// content : Thread Launch Synchronization

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
        trace(); m_flag.wait(false);

        trace();
    }

//  --------------------------------------------------------------------------------

    void release()
    {
        m_flag = true;

        m_flag.notify_all();
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