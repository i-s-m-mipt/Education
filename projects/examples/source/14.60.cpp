////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

////////////////////////////////////////////////////////////////////////////////////

// section : Processes

////////////////////////////////////////////////////////////////////////////////////

// content : Synchronization
//
// content : Process Launch Synchronization

////////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <format>
#include <iostream>
#include <mutex>
#include <syncstream>
#include <thread>

////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

////////////////////////////////////////////////////////////////////////////////////

#include <sys/wait.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////////

using mutex_t     = boost::interprocess::interprocess_mutex;

using condition_t = boost::interprocess::interprocess_condition;

////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(bool * x, mutex_t * mutex, condition_t * condition)
    :
        m_x(x), m_mutex(mutex), m_condition(condition)
    {}

//  --------------------------------------------------------------------------------

    void test() const
    {
        trace();

        {
            std::unique_lock < mutex_t > lock(*m_mutex);

            while (!*m_x)
            {
                m_condition->wait(lock);
            }
        }

        trace();
    }

//  --------------------------------------------------------------------------------

    void release() const
    {
        std::scoped_lock < mutex_t > lock(*m_mutex);

        *m_x = true;

        m_condition->notify_all();
    }

private :

    void trace() const
    {
        auto id = getpid();

        std::osyncstream(std::cout) << std::format("Entity::trace : id = {}\n", id);
    }

//  --------------------------------------------------------------------------------

    bool * m_x = nullptr;

    mutex_t * m_mutex = nullptr;

    condition_t * m_condition = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////

auto make_entity(boost::interprocess::managed_shared_memory & storage)
{
    return Entity
    (
        storage.find_or_construct < bool        > ("x"        )(),

        storage.find_or_construct < mutex_t     > ("mutex"    )(),

        storage.find_or_construct < condition_t > ("condition")()
    );
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    using shared_memory_t = boost::interprocess::managed_shared_memory;

//  -------------------------------------------------------------------------

	auto path = "output";

//  -------------------------------------------------------------------------

	boost::interprocess::shared_memory_object::remove(path);

//  -------------------------------------------------------------------------

	shared_memory_t storage(boost::interprocess::create_only, path, 1 << 10);

//  -------------------------------------------------------------------------

    auto entity = make_entity(storage);

//  -------------------------------------------------------------------------

    auto size = 2uz;

//  -------------------------------------------------------------------------

    for (auto i = 0uz; i < size; ++i)
    {
        if (auto id = fork(); id == 0)
        {
            shared_memory_t storage(boost::interprocess::open_only, path);

        //  --------------------------------------------------------------

            make_entity(storage).test();

        //  --------------------------------------------------------------

            return 0;
        }
    }

//  -------------------------------------------------------------------------

    std::this_thread::sleep_for(1s);

//  -------------------------------------------------------------------------

    entity.release();

//  -------------------------------------------------------------------------

    for (auto i = 0uz; i < size; ++i)
    {
        wait(nullptr);
    }

//  -------------------------------------------------------------------------

	boost::interprocess::shared_memory_object::remove(path);
}

////////////////////////////////////////////////////////////////////////////////////