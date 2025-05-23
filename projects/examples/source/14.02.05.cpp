//////////////////////////////////////////////////////

#include <cassert>
#include <mutex>

//////////////////////////////////////////////////////

class Entity
{
public :

    auto get() const
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        return m_x;
    }

//  --------------------------------------------------

    template < typename F > void invoke(F && f)
    {
        std::scoped_lock < std::mutex > lock(m_mutex);

        f(m_x);
    }

private :

    int m_x = 0;

//  --------------------------------------------------

    mutable std::mutex m_mutex;
};

//////////////////////////////////////////////////////

int * g_x = nullptr;

//////////////////////////////////////////////////////

void test(int & x)
{
    g_x = &x;
}

//////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  --------------------------

    entity.invoke(test);

//  --------------------------

    ++(*g_x);

//  --------------------------

    assert(entity.get() == 1);
}

//////////////////////////////////////////////////////