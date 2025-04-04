/////////////////////////////////////////////////////////////////

#include <cassert>

/////////////////////////////////////////////////////////////////

#include <boost/operators.hpp>

/////////////////////////////////////////////////////////////////

class Entity 
: 
    private boost::less_than_comparable < Entity > ,
     
    private boost::          equivalent < Entity >
{
public :

    Entity(int x) : m_x(x) {}

//  -------------------------------------------------------------

    friend auto operator<(const Entity & lhs, const Entity & rhs)
    {
        return lhs.m_x < rhs.m_x;
    }

private :

    int m_x = 0;
};

/////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////