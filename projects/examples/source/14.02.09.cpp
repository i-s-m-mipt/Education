////////////////////////////////////////////////////////////

#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_semaphore(0) {}

//  --------------------------------------------------------

    void test(int x) const
    {
        std::cout << "Entity::test (1) : x = " << x << '\n';
        
        m_semaphore.acquire();

        std::cout << "Entity::test (2) : x = " << x << '\n'; 
        
        m_semaphore.release();

        std::cout << "Entity::test (3) : x = " << x << '\n';
    }

//  --------------------------------------------------------

    void release() const
    {   
        m_semaphore.release(m_semaphore.max());
    }

private :

    mutable std::counting_semaphore < 2 > m_semaphore;
};

////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -------------------------------------------------

    std::jthread thread_1(&Entity::test, &entity, 1);

    std::jthread thread_2(&Entity::test, &entity, 2);

    std::jthread thread_3(&Entity::test, &entity, 3);

//  -------------------------------------------------

    std::this_thread::sleep_for(1s);

//  -------------------------------------------------

    entity.release();
}

////////////////////////////////////////////////////////////