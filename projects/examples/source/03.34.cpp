////////////////////////////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

////////////////////////////////////////////////////////////////////////////

// section : Operator Overloading

////////////////////////////////////////////////////////////////////////////

// content : Operator <=>
//
// content : Ordering std::strong_ordering
//
// content : Rewritten Expressions

////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <compare>

////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int x, int y) : m_x(x), m_y(y) {}

//  --------------------------------------------------

    auto operator<=>(Entity const & other) const
    { 
        auto comparison = m_x <=> other.m_x;

        if (comparison != std::strong_ordering::equal)
        {
            return comparison;
        }

        return m_y <=> other.m_y;
    }

//  --------------------------------------------------

    auto operator== (Entity const & other) const
    {
        return m_x == other.m_x && m_y == other.m_y;
    }

private :

    int m_x = 0, m_y = 0;
};

////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1(1, 1);

    Entity entity_2(2, 2);

//  ------------------------------------------------------------------------

    assert((entity_1 <=> entity_2) <  0);

    assert((entity_2 <=> entity_2) == 0);

    assert((entity_2 <=> entity_1) >  0);

//  ------------------------------------------------------------------------

    assert((entity_1 <   entity_2) == 1); // support : compiler-explorer.com

    assert((entity_1 >   entity_2) == 0);

    assert((entity_1 <=  entity_2) == 1);

    assert((entity_1 >=  entity_2) == 0);

//  ------------------------------------------------------------------------

    assert((entity_1 ==  entity_2) == 0); // support : compiler-explorer.com

    assert((entity_1 !=  entity_2) == 1);
}

////////////////////////////////////////////////////////////////////////////