//////////////////////////////////////////////////////////////////////

#include <cassert>
#include <compare>

//////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int x, int y) : m_x(x), m_y(y) {}

//  ----------------------------------------------------------------

    auto operator<=>(Entity const & other) const
    {
        if (m_x < other.m_x) { return std::weak_ordering::less;    }

        if (m_x > other.m_x) { return std::weak_ordering::greater; }

        return std::weak_ordering::equivalent;
    }

private :

    int m_x = 0, m_y = 0;
};

//////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1(1, 1);
    
    Entity entity_2(2, 2);

    Entity entity_3(2, 3);

//  ------------------------------------------------------------------

    assert((entity_1 <=> entity_2) <  0);

    assert((entity_2 <=> entity_3) == 0);

    assert((entity_2 <=> entity_1) >  0);

//  ------------------------------------------------------------------

    assert((entity_2 <=> entity_3) == std::weak_ordering::equivalent);
}

//////////////////////////////////////////////////////////////////////