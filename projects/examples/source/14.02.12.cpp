///////////////////////////////////////////////////////////

#include <barrier>
#include <iostream>
#include <syncstream>
#include <thread>

///////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int x) : m_stream(std::cout), m_barrier(x) {}

//  ------------------------------------------------------

    void execute_v1(int x) const
    {
        test(x); m_barrier.arrive_and_wait();

        test(x); m_barrier.arrive_and_wait();

        test(x);
    }

//  ------------------------------------------------------

    void execute_v2(int x) const
    {
        test(x); m_barrier.arrive_and_drop();

        test(x);
    }

private :

    class Callback
    {
    public :

        void operator()() const
        {
            std::cout << "Entity::Callback::operator()\n";
        }
    };

//  ------------------------------------------------------

    void test(int x) const
    {
        m_stream << "Entity::test : x = " << x << '\n';
    }

//  ------------------------------------------------------

    mutable std::osyncstream m_stream;

    mutable std::barrier < Callback > m_barrier;
};

///////////////////////////////////////////////////////////

int main()
{
    Entity entity(3);

//  -------------------------------------------------------

    std::jthread thread_1(&Entity::execute_v1, &entity, 1);

    std::jthread thread_2(&Entity::execute_v1, &entity, 2);

    std::jthread thread_3(&Entity::execute_v2, &entity, 3);
}

///////////////////////////////////////////////////////////