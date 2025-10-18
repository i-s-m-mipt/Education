//////////////////////////////////////////////////////////

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <syncstream>
#include <thread>

//////////////////////////////////////////////////////////

using namespace std::literals;

//////////////////////////////////////////////////////////

class Entity
{
public :

    void test() const
    {
        trace();

        {
            std::unique_lock < std::mutex > lock(m_mutex);

            while (!m_x)
            {
                m_condition.wait(lock);
            }
        }
        
        trace();
    }

//  ------------------------------------------------------

    void release() const
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        m_x = true;

        m_condition.notify_all();
    }

private :

    void trace() const
    {
        std::osyncstream stream(std::cout);

        auto id = std::this_thread::get_id();

        stream << "Entity::trace : id = " << id << '\n';
    }

//  ------------------------------------------------------

    mutable bool m_x = false;

    mutable std::mutex m_mutex;

    mutable std::condition_variable m_condition;
};

//////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -----------------------------------------------

    std::jthread jthread_1(&Entity::test, &entity);

    std::jthread jthread_2(&Entity::test, &entity);

//  -----------------------------------------------

    std::this_thread::sleep_for(1s);

//  -----------------------------------------------

    entity.release();
}

//////////////////////////////////////////////////////////