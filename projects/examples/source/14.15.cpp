////////////////////////////////////////////////////////

// chapter : Parallelism

////////////////////////////////////////////////////////

// section : Synchronization

////////////////////////////////////////////////////////

// content : Synchronization
//
// content : Race Conditions
//
// content : Synchronization Primitives
//
// content : Mutexes
//
// content : Primitive std::mutex
//
// content : Wrapper std::scoped_lock

////////////////////////////////////////////////////////

#include <mutex>
#include <print>
#include <thread>

////////////////////////////////////////////////////////

class Entity
{
public :

//  void test_v1() // error
//  {
//      ++m_x;
//  }

//  ----------------------------------------------------

//  void test_v2() // bad
//  {
//      m_mutex.lock();
//
//      ++m_x;
//
//      m_mutex.unlock();
//  }

//  ----------------------------------------------------

    void test_v3()
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        ++m_x;
    }

//  ----------------------------------------------------

    void test_v4() const
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        std::print("Entity::test_v4 : m_x = {}\n", m_x);
    }

private :

    int m_x = 0;

//  ----------------------------------------------------

    mutable std::mutex m_mutex;
};

////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -------------------------------------------------

    std::jthread thread_1(&Entity::test_v3, &entity);

    std::jthread thread_2(&Entity::test_v4, &entity);
}

////////////////////////////////////////////////////////