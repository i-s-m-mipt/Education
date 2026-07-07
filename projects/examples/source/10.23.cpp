///////////////////////////////////////////////////////////////////

// chapter : Programming with Containers

///////////////////////////////////////////////////////////////////

// content : Multidimensional Subscript Operator

///////////////////////////////////////////////////////////////////

#include <cstddef>

///////////////////////////////////////////////////////////////////

template < typename T, std::size_t S1, std::size_t S2 > class Array
{
public :

	auto & operator[](std::size_t i, std::size_t j)
	{
        return m_array[i][j];
	}

private :

	T m_array[S1][S2]{};
};

///////////////////////////////////////////////////////////////////

int main()
{
    auto const size = 5uz;

//  -------------------------------------

    Array < int, size, size > array;

//  -------------------------------------

    for (auto i = 0uz; i < size; ++i)
    {
        for (auto j = 0uz; j < size; ++j)
        {
            array[i, j] = j + 1;
        }
    }
}

///////////////////////////////////////////////////////////////////