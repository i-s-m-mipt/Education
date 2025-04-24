///////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <syncstream>
#include <thread>

///////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    void execute() const
    {
        test();

        {
            std::unique_lock < std::mutex > lock(m_mutex);

            while (!m_x)
            {
                m_condition.wait(lock);
            }
        }
        
        test();
    }

//  ---------------------------------------------------------------------------

    void release() const
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        m_x = true;

        m_condition.notify_all();
    }

private :

    void test() const
    {
        std::osyncstream stream(std::cout);

        stream << "Entity::test : id = " << std::this_thread::get_id() << '\n';
    }

//  ---------------------------------------------------------------------------

    mutable bool m_x = false;

    mutable std::mutex m_mutex;

    mutable std::condition_variable m_condition;
};

///////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -------------------------------------------------

    std::jthread thread_1(&Entity::execute, &entity);

    std::jthread thread_2(&Entity::execute, &entity);

//  -------------------------------------------------

    std::this_thread::sleep_for(1s);

//  -------------------------------------------------

    entity.release();
}

///////////////////////////////////////////////////////////////////////////////