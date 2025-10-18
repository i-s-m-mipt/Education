/////////////////////////////////////////////////////////////

#include <atomic>
#include <cassert>
#include <thread>

/////////////////////////////////////////////////////////////

class Entity
{
public :

    void test_v1()
    {
        m_x.store(true, std::memory_order::seq_cst);

        m_y.store(true, std::memory_order::seq_cst);
    }

//  ---------------------------------------------------------

    void test_v2()
    {
        while (m_y.load(std::memory_order::seq_cst) == false)
        {
            std::this_thread::yield();
        }

        assert(m_x.load(std::memory_order::seq_cst));
    }

private :

    std::atomic < bool > m_x = false, m_y = false;
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