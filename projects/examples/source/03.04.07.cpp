////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

class Vector 
{
public :

    Vector(std::initializer_list < int > list) : m_vector(list) {}

//  --------------------------------------------------------------------------------

    const auto & operator[](std::size_t index) const 
    {
        std::cout << "Vector::operator[] (1)\n";
    
    //  ----------------------------------------

        return m_vector[index];
    }

//  --------------------------------------------------------------------------------

    auto & operator[](std::size_t index)
    {
        std::cout << "Vector::operator[] (2)\n";

    //  ----------------------------------------------------------------------------

        return const_cast < int & > (static_cast < const Vector & > (*this)[index]);
    }

private :

    std::vector < int > m_vector;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    const auto x = 1, & y = x;

//  ----------------------------------

    const_cast < int & > (y) = 2;

//  ----------------------------------
    
    assert(x == 2);

//  ----------------------------------

    Vector vector = { 1, 2, 3, 4, 5 };

//  ----------------------------------
        
    assert(vector[0] == 1);
}

////////////////////////////////////////////////////////////////////////////////////