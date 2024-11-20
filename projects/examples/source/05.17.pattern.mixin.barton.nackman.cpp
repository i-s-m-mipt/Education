#include <cassert>
#include <iostream>

#include <boost/operators.hpp>

//  ================================================================================================

template < typename T > class Comparable
{
protected:

    Comparable() = default;

public:

    friend auto operator> (const T & lhs, const T & rhs) { return  (rhs < lhs); }
    friend auto operator<=(const T & lhs, const T & rhs) { return !(lhs > rhs); }
    friend auto operator>=(const T & lhs, const T & rhs) { return !(lhs < rhs); }
    friend auto operator==(const T & lhs, const T & rhs)
    {
        return !(lhs < rhs) && !(rhs < lhs);
    }
};

//  ================================================================================================

class Entity_v1 : private Comparable < Entity_v1 >
{
public:

    explicit Entity_v1(int data) : m_data(data) {}

//  -------------------------------------------------------------------

    friend auto operator<(const Entity_v1 & lhs, const Entity_v1 & rhs)
    {
        return lhs.m_data < rhs.m_data;
    }

private:

    int m_data = 0;
}; 

//  ================================================================================================

class Entity_v2 
: 
    private boost::less_than_comparable < Entity_v2 > , 
    private boost::          equivalent < Entity_v2 >
{
public:

    explicit Entity_v2(int data) : m_data(data) {}

//  -------------------------------------------------------------------

    friend auto operator<(const Entity_v2 & lhs, const Entity_v2 & rhs)
    {
        return lhs.m_data < rhs.m_data;
    }

private:

    int m_data = 0;
};

//  ================================================================================================

int main() 
{    
    auto f = false, t = true;

//  -------------------------

    Entity_v1 entity_v1_1(1);
    Entity_v1 entity_v1_2(2);

    assert((entity_v1_1 <  entity_v1_2) == t);
    assert((entity_v1_1 >  entity_v1_2) == f);
    assert((entity_v1_1 <= entity_v1_2) == t);
    assert((entity_v1_1 >= entity_v1_2) == f);
    assert((entity_v1_1 == entity_v1_2) == f);
    assert((entity_v1_1 != entity_v1_2) == t);

//  ------------------------------------------

    Entity_v2 entity_v2_1(1);
    Entity_v2 entity_v2_2(2);

    assert((entity_v2_1 <  entity_v2_2) == t);
    assert((entity_v2_1 >  entity_v2_2) == f);
    assert((entity_v2_1 <= entity_v2_2) == t);
    assert((entity_v2_1 >= entity_v2_2) == f);
    assert((entity_v2_1 == entity_v2_2) == f);
    assert((entity_v2_1 != entity_v2_2) == t);
}