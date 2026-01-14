/////////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <mutex>
#include <print>
#include <thread>

/////////////////////////////////////////////////////////////////////////////////////

class Spinlock
{ 
public :

    void lock() // support : compiler-explorer.com
    {
        auto expected = false;

        while(!m_x.compare_exchange_weak(expected, true, std::memory_order::acquire))
        {
            expected = false;
        } 
    }

//  ---------------------------------------------------------------------------------

    void unlock()
    {
        m_x.store(false, std::memory_order::release);
    }

private :

    std::atomic < bool > m_x = false;
};

/////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    void test_v1()
    {
        std::scoped_lock < Spinlock > lock(m_spinlock);

        ++m_x;
    }

//  ----------------------------------------------------

    void test_v2() const
    {
        std::scoped_lock < Spinlock > lock(m_spinlock);

        std::print("Entity::test_v2 : m_x = {}\n", m_x);
    }

private :

    int m_x = 0;

//  ----------------------------------------------------

    mutable Spinlock m_spinlock;
};

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  --------------------------------------------------

    std::jthread jthread_1(&Entity::test_v1, &entity);

    std::jthread jthread_2(&Entity::test_v2, &entity);
}

/////////////////////////////////////////////////////////////////////////////////////