/////////////////////////////////////////////////////////////

#include <memory>
#include <mutex>
#include <thread>

/////////////////////////////////////////////////////////////

class Entity
{
public :

    using mutex_t = std::mutex;

//  ---------------------------------------------------------

    Entity()
    {
    //  initialize_v1(); // bad

        std::call_once(m_flag, &Entity::initialize_v2, this);
    }

private :

//  void initialize_v1() // bad
//  {
//      if (!m_x)
//      {
//          std::scoped_lock < mutex_t > lock(m_mutex);
//
//          if (!m_x)
//          {
//              m_x = std::make_unique < int > (1);
//          }
//      }
//  }

//  ---------------------------------------------------------

    void initialize_v2()
    {
        m_x = std::make_unique < int > (1);
    }

//  ---------------------------------------------------------

    std::unique_ptr < int > m_x;

//  ---------------------------------------------------------

    mutable mutex_t m_mutex;

    mutable std::once_flag m_flag;
};

/////////////////////////////////////////////////////////////

void test()
{
    Entity entity;
}

/////////////////////////////////////////////////////////////

int main()
{
    std::jthread thread_1(test);

    std::jthread thread_2(test);
}

/////////////////////////////////////////////////////////////