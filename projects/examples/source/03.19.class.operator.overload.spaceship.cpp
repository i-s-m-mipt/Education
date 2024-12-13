#include <cassert>
#include <compare>
#include <string>

////////////////////////////////////////////////////////////////////////////////////

class Entity_v1
{
public:

    explicit Entity_v1(int data) : m_data(data) {}

//  ---------------------------------------------------------------------

    friend auto operator<=>(const Entity_v1 & lhs, const Entity_v1 & rhs) 
    { 
        return lhs.m_data <=> rhs.m_data; 
    }

private:

    int m_data = 0;
};

////////////////////////////////////////////////////////////////////////////////////

class Entity_v2
{
public:

    explicit Entity_v2(int data_1, int data_2) 
    : 
        m_data_1(data_1), 
        m_data_2(data_2) 
    {}

//  --------------------------------------------------------------------------------

    friend auto operator<=>(const Entity_v2 & lhs, const Entity_v2 & rhs) = default; 

private:

    int m_data_1 = 0; 
    int m_data_2 = 0;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert((1 <=> 1) == 0);
    assert((1 <=> 2) <  0);
    assert((2 <=> 1) >  0);

//  ---------------------------------------------------

    auto f = false, t = true;

//  ---------------------------------------------------

    Entity_v1 entity_v1_1(1);
    Entity_v1 entity_v1_2(2);

    assert((entity_v1_1 <  entity_v1_2) == t);
    assert((entity_v1_1 >  entity_v1_2) == f);
    assert((entity_v1_1 <= entity_v1_2) == t);
    assert((entity_v1_1 >= entity_v1_2) == f);
//  assert((entity_v1_1 == entity_v1_2) == f); // error
//  assert((entity_v1_1 != entity_v1_2) == t); // error

//  ---------------------------------------------------

    Entity_v2 entity_v2_1(1, 1);
    Entity_v2 entity_v2_2(2, 2);

    assert((entity_v2_1 <  entity_v2_2) == t);
    assert((entity_v2_1 >  entity_v2_2) == f);
    assert((entity_v2_1 <= entity_v2_2) == t);
    assert((entity_v2_1 >= entity_v2_2) == f);
    assert((entity_v2_1 == entity_v2_2) == f);
    assert((entity_v2_1 != entity_v2_2) == t);
}