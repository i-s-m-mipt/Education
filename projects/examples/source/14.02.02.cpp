///////////////////////////////////////////////////////////////

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

///////////////////////////////////////////////////////////////

class Entity
{
public :

    using mutex_t = std::shared_mutex;

//  -----------------------------------------------------------

    void test_v1()
    {
        std::scoped_lock < mutex_t > lock(m_mutex);

        ++m_x;
    }

//  -----------------------------------------------------------

    void test_v2() const
    {
        std::shared_lock < mutex_t > lock(m_mutex);

        std::cout << "Entity::test_v2 : m_x = " << m_x << '\n';
    }

private :

    int m_x = 0;

//  -----------------------------------------------------------

    mutable mutex_t m_mutex;
};

///////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -------------------------------------------------

    std::jthread thread_1(&Entity::test_v1, &entity);

    std::jthread thread_2(&Entity::test_v2, &entity);

    std::jthread thread_3(&Entity::test_v2, &entity);
}

///////////////////////////////////////////////////////////////