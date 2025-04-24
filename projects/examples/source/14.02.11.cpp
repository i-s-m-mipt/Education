///////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <iostream>
#include <semaphore>
#include <syncstream>
#include <thread>

///////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_semaphore(0) {}

//  ---------------------------------------------------------------------------

    void execute() const
    {
        test(); m_semaphore.acquire();

        test(); m_semaphore.release();
    }

//  ---------------------------------------------------------------------------

    void release() const
    {   
        m_semaphore.release(m_semaphore.max());
    }

private :

    void test() const
    {
        std::osyncstream stream(std::cout);

        stream << "Entity::test : id = " << std::this_thread::get_id() << '\n';
    }

//  ---------------------------------------------------------------------------

    mutable std::counting_semaphore < 2 > m_semaphore;
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