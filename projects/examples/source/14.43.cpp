/////////////////////////////////////////////////////////////

// chapter : Parallel Programming

/////////////////////////////////////////////////////////////

// content : Acquire-Release Semantics
//
// content : Store-Release and Load-Acquire Fences
//
// content : Happens-Before and Synchronizes-With Relations
//
// content : Total Strong Ordering (TSO)
//
// content : Allowed Store-Load Reordering
//
// content : Preventing Optimizations

/////////////////////////////////////////////////////////////

#include <atomic>
#include <cassert>
#include <thread>

/////////////////////////////////////////////////////////////

class Entity
{
public :

    void test_v1() // support : https://compiler-explorer.com
    {
        m_x.store(1, std::memory_order::relaxed);

        m_y.store(1, std::memory_order::release);
    }

//  ---------------------------------------------------------

    void test_v2()
    {
        while (m_y.load(std::memory_order::acquire) == 0)
        {
            std::this_thread::yield();
        }

        assert(m_x.load(std::memory_order::relaxed) == 1);
    }

private :

    std::atomic < int > m_x = 0, m_y = 0;
};

/////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  --------------------------------------------------

    std::jthread jthread_1(&Entity::test_v1, &entity);

    std::jthread jthread_2(&Entity::test_v2, &entity);
}

/////////////////////////////////////////////////////////////