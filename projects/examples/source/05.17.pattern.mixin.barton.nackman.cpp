#include <cassert>

#include <boost/operators.hpp>

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

class Entity_v1 : private Comparable < Entity_v1 >
{
public:

    Entity_v1(int data) : m_data(data) {}

//  -------------------------------------------------------------------

    friend auto operator<(const Entity_v1 & lhs, const Entity_v1 & rhs)
    {
        return lhs.m_data < rhs.m_data;
    }

private:

    int m_data = 0;
}; 

/////////////////////////////////////////////////////////////////////////////////

class Entity_v2 
: 
    private boost::less_than_comparable < Entity_v2 > , 
    private boost::          equivalent < Entity_v2 >
{
public:

    Entity_v2(int data) : m_data(data) {}

//  -------------------------------------------------------------------

    friend auto operator<(const Entity_v2 & lhs, const Entity_v2 & rhs)
    {
        return lhs.m_data < rhs.m_data;
    }

private:

    int m_data = 0;
};

/////////////////////////////////////////////////////////////////////////////////

int main() 
{    
    {
        Entity_v1 entity_v1_1(1), entity_v1_2(2);

        assert((entity_v1_1 <  entity_v1_2) == 1);
        assert((entity_v1_1 >  entity_v1_2) == 0);
        assert((entity_v1_1 <= entity_v1_2) == 1);
        assert((entity_v1_1 >= entity_v1_2) == 0);
        assert((entity_v1_1 == entity_v1_2) == 0);
        assert((entity_v1_1 != entity_v1_2) == 1);
    }

//  ----------------------------------------------

    {
        Entity_v2 entity_v2_1(1), entity_v2_2(2);

        assert((entity_v2_1 <  entity_v2_2) == 1);
        assert((entity_v2_1 >  entity_v2_2) == 0);
        assert((entity_v2_1 <= entity_v2_2) == 1);
        assert((entity_v2_1 >= entity_v2_2) == 0);
        assert((entity_v2_1 == entity_v2_2) == 0);
        assert((entity_v2_1 != entity_v2_2) == 1);
    }
}