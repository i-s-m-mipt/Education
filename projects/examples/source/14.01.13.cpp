//////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

//////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

//////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_future(m_promise.get_future()) {}

//  ------------------------------------------------------------------------------

    void execute() const
    {
        test(); m_future.wait();

        test();
    }

//  ------------------------------------------------------------------------------

    void release() const
    {
        m_promise.set_value();
    }

private :

    void test() const
    {
        std::cout << "Entity::test : id = " << std::this_thread::get_id() << '\n';
    }

//  ------------------------------------------------------------------------------

    mutable std::promise < void > m_promise;

    mutable std::shared_future < void > m_future;
};

//////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////