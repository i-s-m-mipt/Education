#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

class Vector 
{
public:

    Vector(std::size_t size, int data = 0) : m_vector(size, data) {}

//  --------------------------------------------------------------------------------

    const auto & operator[](std::size_t index) const 
    {
        std::cout << "Vector::operator[] (1)\n";

        return m_vector[index];
    }

    auto & operator[](std::size_t index)
    {
        std::cout << "Vector::operator[] (2)\n";

        return const_cast < int & > (static_cast < const Vector & > (*this)[index]);
    }

private:

    std::vector < int > m_vector;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        auto x = 1; const auto & r_x = x;

        const_cast < int & > (r_x) = 2; 
    
        assert(x == 2);
    }

//  ------------------------------------------------

    {
        Vector vector(5, 0); assert(vector[0] == 0);
    }
}