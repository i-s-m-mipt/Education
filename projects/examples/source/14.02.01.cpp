///////////////////////////////////////////////////////////////

#include <iostream>
#include <mutex>
#include <thread>

///////////////////////////////////////////////////////////////

class Entity
{
public :

//  void test_v1() // error
//  {
//      ++m_x;
//  }

//  -----------------------------------------------------------

    void test_v2()
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        ++m_x;
    }

//  -----------------------------------------------------------

    void test_v3() const
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        std::cout << "Entity::test_v3 : m_x = " << m_x << '\n';
    }

private :

    int m_x = 0;

//  -----------------------------------------------------------

    mutable std::mutex m_mutex;
};

///////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -------------------------------------------------

    std::jthread thread_1(&Entity::test_v2, &entity);

    std::jthread thread_2(&Entity::test_v3, &entity);
}

///////////////////////////////////////////////////////////////