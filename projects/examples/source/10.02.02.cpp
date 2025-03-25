#include <cstddef>

///////////////////////////////////////////////////////////////////

template < typename T, std::size_t S1, std::size_t S2 > class Array
{
public :

	class View 
	{
	public :

		View(T (&array)[S2]) : m_array(array) {}

	//  ----------------------------------------

		auto & operator[](std::size_t index)
		{ 
			return m_array[index];
		}

	private :

		T (&m_array)[S2];
	};

//  --------------------------------------------

	auto operator[](std::size_t index)
	{ 
		return View(m_array[index]);
	}

private :

	T m_array[S1][S2]{};
};

///////////////////////////////////////////////////////////////////

int main()
{
    constexpr auto size = 5uz;

//  -------------------------------------

    Array < int, size, size > array;

//  -------------------------------------

    for (auto i = 0uz; i < size; ++i)
    {
        for (auto j = 0uz; j < size; ++j)
        {
            array[i][j] = j + 1;
        }
    }
}