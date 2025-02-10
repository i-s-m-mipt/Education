#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////

class Entity 
{
public:

    Entity(std::initializer_list < int > list) : m_data(list) {}

//  --------------------------------------------------------------------------------------

    const auto & operator[](std::size_t index) const 
    {
        std::cout << "Entity::operator[] (1)\n";

        return m_data[index];
    }

    auto & operator[](std::size_t index)
    {
        std::cout << "Entity::operator[] (2)\n";

        return const_cast < int & > (static_cast < const Entity & > (*this)[index]);
    }

private:

    std::vector < int > m_data;
};

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        auto x = 1;
        
        const auto & r_x = x;

        const_cast < int & > (r_x) = 2;
    
        assert(x == 2);
    }

//  --------------------------------------

    {
        Entity entity = { 1, 2, 3, 4, 5 };
        
        assert(entity[0] == 1);
    }
}