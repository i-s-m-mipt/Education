/////////////////////////////////////////////////////////////

#include <memory>
#include <mutex>
#include <thread>

/////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity()
    {
    //  initialize_v1(); // error

        std::call_once(m_flag, &Entity::initialize_v2, this);
    }

private :

//  void initialize_v1() // error
//  {
//      if (!s_x)
//      {
//          std::scoped_lock < std::mutex > lock(m_mutex);
//
//          if (!s_x)
//          {
//              s_x = std::make_unique < int > (1);
//          }
//      }
//  }

//  ---------------------------------------------------------

    void initialize_v2()
    {
        s_x = std::make_unique < int > (1);
    }

//  ---------------------------------------------------------

    static inline std::unique_ptr < int > s_x;

//  ---------------------------------------------------------

    mutable std::mutex m_mutex;

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
    std::jthread jthread_1(test);

    std::jthread jthread_2(test);
}

/////////////////////////////////////////////////////////////