/////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

/////////////////////////////////////////////////////////////////////////

// content : Thread-Safe Initialization
//
// content : Pattern Double-Checked Locking
//
// content : Function std::call_once
//
// content : Flag std::once_flag

/////////////////////////////////////////////////////////////////////////

#include <memory>
#include <mutex>
#include <thread>

/////////////////////////////////////////////////////////////////////////

class Entity
{
public :

//  void initialize_v1() // error
//  {
//      if (!m_x)
//      {
//          std::scoped_lock < std::mutex > lock(m_mutex);
//
//          if (!m_x)
//          {
//              m_x = std::make_shared < int > (1);
//          }
//      }
//  }

//  ---------------------------------------------------------------------

    void initialize_v2()
    {
        std::call_once(m_flag, &Entity::initialize_implementation, this);
    }

private :

    void initialize_implementation()
    {
        m_x = std::make_shared < int > (1);
    }

//  ---------------------------------------------------------------------

    std::shared_ptr < int > m_x;

    std::once_flag m_flag;

//  ---------------------------------------------------------------------

    mutable std::mutex m_mutex;
};

/////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -------------------------------------------------------

    std::jthread thread_1(&Entity::initialize_v2, &entity);

    std::jthread thread_2(&Entity::initialize_v2, &entity);
}

/////////////////////////////////////////////////////////////////////////