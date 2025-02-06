#include <cassert>
#include <compare>

////////////////////////////////////////////////////////////////////////////////////

class Entity_v1 // оператор не член
{
public:

    Entity_v1(int x) : m_data(x) {}

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

    Entity_v2(int x, int y) : m_data_1(x), m_data_2(y) {}

//  --------------------------------------------------------------------------------

    friend auto operator<=>(const Entity_v2 & lhs, const Entity_v2 & rhs) = default;

private:

    int m_data_1 = 0, m_data_2 = 0;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        assert((1 <=> 1) == 0);
        assert((1 <=> 2) <  0);
        assert((2 <=> 1) >  0);
    }

//  -------------------------------------------------------

    {
        Entity_v1 entity_v1_1(1), entity_v1_2(2);

        assert((entity_v1_1 <  entity_v1_2) == 1);
        assert((entity_v1_1 >  entity_v1_2) == 0);
        assert((entity_v1_1 <= entity_v1_2) == 1);
        assert((entity_v1_1 >= entity_v1_2) == 0);
//      assert((entity_v1_1 == entity_v1_2) == 0); // error
//      assert((entity_v1_1 != entity_v1_2) == 1); // error
    }

//  -------------------------------------------------------

    {
        Entity_v2 entity_v2_1(1, 1), entity_v2_2(2, 2);

        assert((entity_v2_1 <  entity_v2_2) == 1);
        assert((entity_v2_1 >  entity_v2_2) == 0);
        assert((entity_v2_1 <= entity_v2_2) == 1);
        assert((entity_v2_1 >= entity_v2_2) == 0);
        assert((entity_v2_1 == entity_v2_2) == 0);
        assert((entity_v2_1 != entity_v2_2) == 1);
    }
}