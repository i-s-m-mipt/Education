///////////////////////////////////////////////////

#include <cassert>
#include <mutex>

///////////////////////////////////////////////////

class Entity
{
public :

    using mutex_t = std::mutex;

//  -----------------------------------------------

    auto get() const
    {
        std::scoped_lock < mutex_t > lock(m_mutex);

        return m_x;
    }

//  -----------------------------------------------

    template < typename F > void invoke(F && f)
    {
        std::scoped_lock < mutex_t > lock(m_mutex);

        f(m_x);
    }

private :

    int m_x = 0;

//  -----------------------------------------------

    mutable mutex_t m_mutex;
};

///////////////////////////////////////////////////

int * g_x = nullptr;

///////////////////////////////////////////////////

void extract(int & x)
{
    g_x = &x;
}

///////////////////////////////////////////////////

int main()
{
    Entity entity;

//  --------------------------

    entity.invoke(extract);

//  --------------------------

    ++(*g_x);

//  --------------------------

    assert(entity.get() == 1);
}

///////////////////////////////////////////////////