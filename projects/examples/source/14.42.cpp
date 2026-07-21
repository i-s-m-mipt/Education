///////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

///////////////////////////////////////////////////////////////////

// content : Memory Ordering
//
// content : Enumeration std::memory_order
//
// content : Relaxed Memory Model
//
// content : Store-Store and Load-Load Reorderings

///////////////////////////////////////////////////////////////////

#include <atomic>
#include <cassert>
#include <thread>

///////////////////////////////////////////////////////////////////

class Entity
{
public :

    void test_v1()
    {
        m_x.store(1, std::memory_order::relaxed);

        m_y.store(1, std::memory_order::relaxed);
    }

//  ---------------------------------------------------------------

    void test_v2()
    {
        while (m_y.load(std::memory_order::relaxed) == 0)
        {
            std::this_thread::yield();
        }

    //  assert(m_x.load(std::memory_order::relaxed) == 1); // error
    }

private :

    std::atomic < int > m_x = 0, m_y = 0;
};

///////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  --------------------------------------------------

    std::jthread jthread_1(&Entity::test_v1, &entity);

    std::jthread jthread_2(&Entity::test_v2, &entity);
}

///////////////////////////////////////////////////////////////////