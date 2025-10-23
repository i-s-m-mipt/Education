///////////////////////////////////////////////////////////////

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

///////////////////////////////////////////////////////////////

class Entity
{
public :

    void test_v1()
    {
        std::scoped_lock < std::shared_mutex > lock(m_mutex);

        ++m_x;
    }

//  -----------------------------------------------------------

    void test_v2() const
    {
        std::shared_lock < std::shared_mutex > lock(m_mutex);

        std::cout << "Entity::test_v2 : m_x = " << m_x << '\n';
    }

private :

    int m_x = 0;

//  -----------------------------------------------------------

    mutable std::shared_mutex m_mutex;
};

///////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  --------------------------------------------------

    std::jthread jthread_1(&Entity::test_v1, &entity);

    std::jthread jthread_2(&Entity::test_v2, &entity);

    std::jthread jthread_3(&Entity::test_v2, &entity);
}

///////////////////////////////////////////////////////////////