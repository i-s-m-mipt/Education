////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    void test() const
    {
        trace(); 
        
        while (!m_x)
        {
            std::this_thread::yield();
        }

        trace(); 
    }

//  ----------------------------------------------------------------------------

    void release() const
    {
        m_x = true;
    }

private :

    void trace() const
    {
        std::osyncstream stream(std::cout);

        stream << "Entity::trace : id = " << std::this_thread::get_id() << '\n';
    }

//  ----------------------------------------------------------------------------

    mutable std::atomic < bool > m_x = false;
};

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////