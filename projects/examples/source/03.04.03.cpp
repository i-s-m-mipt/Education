////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <compare>

////////////////////////////////////////////////////////////////////////////////////

class Entity_v1
{
public :

    Entity_v1(int x, int y) : m_x(x), m_y(y) {}

//  ---------------------------------------------------------------------

    friend auto operator<=>(Entity_v1 const & lhs, Entity_v1 const & rhs) 
    { 
        auto comparison = lhs.m_x <=> rhs.m_x;

        if (comparison != std::strong_ordering::equal)
        {
            return comparison;
        }

        return lhs.m_y <=> rhs.m_y;
    }

private :

    int m_x = 0, m_y = 0;
};

////////////////////////////////////////////////////////////////////////////////////

class Entity_v2
{
public :

    Entity_v2(int x, int y) : m_x(x), m_y(y) {}

//  --------------------------------------------------------------------------------

    friend auto operator<=>(Entity_v2 const & lhs, Entity_v2 const & rhs) = default;

private :

    int m_x = 0, m_y = 0;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert((2 <=> 1) >  0);

    assert((1 <=> 1) == 0);

    assert((1 <=> 2) <  0);
    
//  ---------------------------------------------------

    Entity_v1 entity_v1_1(1, 1);
    
    Entity_v1 entity_v1_2(2, 2);

//  ---------------------------------------------------

    assert((entity_v1_1 <  entity_v1_2) == 1);

    assert((entity_v1_1 >  entity_v1_2) == 0);

    assert((entity_v1_1 <= entity_v1_2) == 1);

    assert((entity_v1_1 >= entity_v1_2) == 0);

//  assert((entity_v1_1 == entity_v1_2) == 0); // error

//  assert((entity_v1_1 != entity_v1_2) == 1); // error

//  ---------------------------------------------------

    Entity_v2 entity_v2_1(1, 1);
    
    Entity_v2 entity_v2_2(2, 2);

//  ---------------------------------------------------

    assert((entity_v2_1 <  entity_v2_2) == 1);

    assert((entity_v2_1 >  entity_v2_2) == 0);

    assert((entity_v2_1 <= entity_v2_2) == 1);

    assert((entity_v2_1 >= entity_v2_2) == 0);

    assert((entity_v2_1 == entity_v2_2) == 0);

    assert((entity_v2_1 != entity_v2_2) == 1);
}

////////////////////////////////////////////////////////////////////////////////////