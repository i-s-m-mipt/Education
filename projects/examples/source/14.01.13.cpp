///////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

///////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_future(m_promise.get_future()) {}

//  -------------------------------------------------------------------------------

    void test() const
    {
        trace(); m_future.wait();

        trace();
    }

//  -------------------------------------------------------------------------------

    void release() const
    {
        m_promise.set_value();
    }

private :

    void trace() const
    {
        std::cout << "Entity::trace : id = " << std::this_thread::get_id() << '\n';
    }

//  -------------------------------------------------------------------------------

    mutable std::promise < void > m_promise;

    mutable std::shared_future < void > m_future;
};

///////////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  ----------------------------------------------

    std::jthread thread_1(&Entity::test, &entity);

    std::jthread thread_2(&Entity::test, &entity);

//  ----------------------------------------------

    std::this_thread::sleep_for(1s);

//  ----------------------------------------------

    entity.release();
}

///////////////////////////////////////////////////////////////////////////////////