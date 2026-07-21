//////////////////////////////////////////////////////////

// chapter : Parallel Programming

//////////////////////////////////////////////////////////

// content : Sequential Consistency
//
// content : Total Ordering
//
// content : Prohibited Store-Load Reordering
//
// content : Pipeline Stalling

//////////////////////////////////////////////////////////

#include <atomic>
#include <cassert>
#include <thread>

//////////////////////////////////////////////////////////

class Entity
{
public :

    void test_v1()
    {
        m_x.store(1, std::memory_order::seq_cst);

        m_y.store(1, std::memory_order::seq_cst);
    }

//  ------------------------------------------------------

    void test_v2()
    {
        while (m_y.load(std::memory_order::seq_cst) == 0)
        {
            std::this_thread::yield();
        }

        assert(m_x.load(std::memory_order::seq_cst) == 1);
    }

private :

    std::atomic < int > m_x = 0, m_y = 0;
};

//////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  --------------------------------------------------

    std::jthread jthread_1(&Entity::test_v1, &entity);

    std::jthread jthread_2(&Entity::test_v2, &entity);
}

//////////////////////////////////////////////////////////