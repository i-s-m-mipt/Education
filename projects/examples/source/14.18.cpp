/////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

/////////////////////////////////////////////////////////////////////////////////

// section : Synchronization

/////////////////////////////////////////////////////////////////////////////////

// content : Deadlocks
//
// content : Function std::lock
//
// content : Wrapper std::lock_guard
//
// content : Object std::adopt_lock
//
// content : Wrapper std::unique_lock
//
// content : Object std::defer_lock
//
// content : Wrapper std::scoped_lock

/////////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <utility>

/////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int x) : m_x(x) {}

//  -----------------------------------------------------------------------------

//  void swap_v1(Entity & other) // bad
//  {
//      std::lock(m_mutex, other.m_mutex);
//
//      std::lock_guard < std::mutex > lock_1(      m_mutex, std::adopt_lock);
//
//      std::lock_guard < std::mutex > lock_2(other.m_mutex, std::adopt_lock);
//
//      std::swap(m_x, other.m_x);
//  }

//  -----------------------------------------------------------------------------

//  void swap_v2(Entity & other) // bad
//  {
//      std::unique_lock < std::mutex > lock_1(      m_mutex, std::defer_lock);
//
//      std::unique_lock < std::mutex > lock_2(other.m_mutex, std::defer_lock);
//
//      std::lock(m_mutex, other.m_mutex);
//
//      std::swap(m_x, other.m_x);
//  }

//  -----------------------------------------------------------------------------

    void swap_v3(Entity & other)
    {
        std::scoped_lock < std::mutex, std::mutex > lock(m_mutex, other.m_mutex);

        std::swap(m_x, other.m_x);
    }

private :

    int m_x = 0;
    
//  -----------------------------------------------------------------------------

    mutable std::mutex m_mutex;
};

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1(1);

    Entity entity_2(2);

//  ---------------------------

    entity_1.swap_v3(entity_2);
}

/////////////////////////////////////////////////////////////////////////////////