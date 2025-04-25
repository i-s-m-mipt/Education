/////////////////////////////////////////////////////////////

#include <atomic>
#include <cassert>
#include <thread>

/////////////////////////////////////////////////////////////

class Entity
{
public :

    void execute_v1()
    {
        m_x.store(true, std::memory_order::seq_cst);

        m_y.store(true, std::memory_order::seq_cst);
    }

//  ---------------------------------------------------------

    void execute_v2()
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

//  ----------------------------------------------------

    std::jthread thread_1(&Entity::execute_v1, &entity);

    std::jthread thread_2(&Entity::execute_v2, &entity);
}

/////////////////////////////////////////////////////////////