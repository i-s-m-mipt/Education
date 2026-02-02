/////////////////////////////////////////////////////////////////////////////////

// chapter : Software Design Patterns

/////////////////////////////////////////////////////////////////////////////////

// section : Mixin-Based Patterns

/////////////////////////////////////////////////////////////////////////////////

// content : Mixin-Based Comparison Operators
//
// content : Barton-Nackman Trick
//
// content : Restricted Template Expansion

/////////////////////////////////////////////////////////////////////////////////

#include <cassert>

/////////////////////////////////////////////////////////////////////////////////

template < typename T > class Comparable // support : cppinsights.io
{
public :

    friend auto operator> (T const & lhs, T const & rhs) { return  (rhs < lhs); }

    friend auto operator<=(T const & lhs, T const & rhs) { return !(lhs > rhs); }

    friend auto operator>=(T const & lhs, T const & rhs) { return !(lhs < rhs); }

protected :

    Comparable() = default;
};

/////////////////////////////////////////////////////////////////////////////////

template < typename T > class Equivalent
{
public :

    friend auto operator==(T const & lhs, T const & rhs)
    {
        return !(lhs < rhs) && !(rhs < lhs);
    }

protected :

    Equivalent() = default;
};

/////////////////////////////////////////////////////////////////////////////////

class Entity 
: 
    private Comparable < Entity > , 
    
    private Equivalent < Entity >
{
public :

    Entity(int x) : m_x(x) {}

//  -------------------------------------------------------------

    friend auto operator<(Entity const & lhs, Entity const & rhs)
    {
        return lhs.m_x < rhs.m_x;
    }

private :

    int m_x = 0;
};

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1(1);
    
    Entity entity_2(2);

//  ------------------------------------

    assert((entity_1 <  entity_2) == 1);
    
    assert((entity_1 >  entity_2) == 0);

    assert((entity_1 <= entity_2) == 1);

    assert((entity_1 >= entity_2) == 0);

    assert((entity_1 == entity_2) == 0);

    assert((entity_1 != entity_2) == 1);
}

/////////////////////////////////////////////////////////////////////////////////