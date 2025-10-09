////////////////////////////////////////////////////////////////

#include <iostream>
#include <mutex>
#include <thread>

////////////////////////////////////////////////////////////////

class Entity
{
public :

    void test_v1()
    {
        std::scoped_lock < std::recursive_mutex > lock(m_mutex);

        ++m_x;

        test_v2();
    }

//  ------------------------------------------------------------

    void test_v2() const
    {
        std::scoped_lock < std::recursive_mutex > lock(m_mutex);

        std::cout << "Entity::test_v2 : m_x = " << m_x << '\n';
    }

private :

    int m_x = 0;

//  ------------------------------------------------------------

    mutable std::recursive_mutex m_mutex;
};

////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -------------------------------------------------

    std::jthread thread_1(&Entity::test_v1, &entity);

    std::jthread thread_2(&Entity::test_v2, &entity);
}

////////////////////////////////////////////////////////////////