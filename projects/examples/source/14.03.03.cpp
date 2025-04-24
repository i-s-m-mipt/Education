///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

///////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    void execute() const
    {
        test(); m_x.wait(false);

        test(); 
    }

//  ---------------------------------------------------------------------------

    void release() const
    {
        m_x = true;

        m_x.notify_all();
    }

private :

    void test() const
    {
        std::osyncstream stream(std::cout);

        stream << "Entity::test : id = " << std::this_thread::get_id() << '\n';
    }

//  ---------------------------------------------------------------------------

    mutable std::atomic < bool > m_x = false;
};

///////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -------------------------------------------------

    std::jthread thread_1(&Entity::execute, &entity);

    std::jthread thread_2(&Entity::execute, &entity);

//  -------------------------------------------------

    std::this_thread::sleep_for(1s);

//  -------------------------------------------------

    entity.release();
}

///////////////////////////////////////////////////////////////////////////////