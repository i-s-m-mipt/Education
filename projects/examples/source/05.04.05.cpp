#include <cassert>

/////////////////////////////////////////////////////////////////////////////////

template < typename T > class Comparable
{
public:

    friend auto operator> (const T & lhs, const T & rhs) { return  (rhs < lhs); }

    friend auto operator<=(const T & lhs, const T & rhs) { return !(lhs > rhs); }

    friend auto operator>=(const T & lhs, const T & rhs) { return !(lhs < rhs); }

    friend auto operator==(const T & lhs, const T & rhs)
    {
        return !(lhs < rhs) && !(rhs < lhs);
    }

protected:

    Comparable() = default;
};

/////////////////////////////////////////////////////////////////////////////////

class Entity : private Comparable < Entity >
{
public:

    Entity(int x) : m_data(x) {}

//  -------------------------------------------------------------

    friend auto operator<(const Entity & lhs, const Entity & rhs)
    {
        return lhs.m_data < rhs.m_data;
    }

private:

    int m_data = 0;
};

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1(1), entity_2(2);

//  ------------------------------------

    assert((entity_1 <  entity_2) == 1);
    
    assert((entity_1 >  entity_2) == 0);

    assert((entity_1 <= entity_2) == 1);

    assert((entity_1 >= entity_2) == 0);

    assert((entity_1 == entity_2) == 0);

    assert((entity_1 != entity_2) == 1);
}