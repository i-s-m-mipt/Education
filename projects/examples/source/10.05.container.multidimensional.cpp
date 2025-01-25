#include <array>
#include <cstddef>
#include <vector>

#include <boost/multi_array.hpp>

////////////////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t S1, std::size_t S2 > class Array
{
public:

	class View 
	{
	public:

		View(T * data) : m_data(data) {}

	//  ------------------------------------

		auto & operator[](std::size_t index)
		{ 
			return m_data[index]; 
		}

	private:

		T * m_data = nullptr;
	};

//  ---------------------------------------------------------------

	auto operator[](std::size_t index)
	{ 
		return View(m_data[index]); 
	}

private:

	T m_data[S1][S2]{};
};

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		constexpr auto size = 5uz;

		[[maybe_unused]] int array[size][size]{};

		for (auto i = 0uz; i < size; ++i)
		{
			for (auto j = 0uz; j < size; ++j)
			{
				array[i][j] = j + 1;
			}
		}
	}

//  ------------------------------------------------------------------------------------

	{
		constexpr auto size = 5uz;

		Array < int, size, size > array;

		for (auto i = 0uz; i < size; ++i)
		{
			for (auto j = 0uz; j < size; ++j)
			{
				array[i][j] = j + 1;
			}
		}
	}

//  ------------------------------------------------------------------------------------

	{
		auto size = 5uz;

		auto array = new int*[size]{};

		for (auto i = 0uz; i < size; ++i)
		{
			array[i] = new int[size]{};
		}

		for (auto i = 0uz; i < size; ++i)
		{
			for (auto j = 0uz; j < size; ++j)
			{
				array[i][j] = j + 1;
			}
		}

		for (auto i = 0uz; i < size; ++i)
		{
			delete[] array[i];
		}

		delete[] array;
	}

//  ------------------------------------------------------------------------------------

	{
		auto size = 5uz;

		auto array = new int[size * size]{};

		for (auto i = 0uz; i < size; ++i)
		{
			for (auto j = 0uz; j < size; ++j)
			{
				array[i * size + j] = j + 1;
			}
		}

		delete[] array;
	}

//  ------------------------------------------------------------------------------------

	{
		constexpr auto size = 5uz;

		std::array < std::array < int, size > , size > array = {};

		for (auto i = 0uz; i < size; ++i)
		{
			for (auto j = 0uz; j < size; ++j)
			{
				array[i][j] = j + 1;
			}
		}
	}

//  ------------------------------------------------------------------------------------

	{
		auto size = 5uz;

		std::vector < std::vector < int > > vector(size, std::vector < int > (size, 0));

		for (auto i = 0uz; i < size; ++i)
		{
			for (auto j = 0uz; j < size; ++j)
			{
				vector[i][j] = j + 1;
			}
		}
	}

//  ------------------------------------------------------------------------------------

	{
		auto size = 5uz;

		boost::multi_array < int, 2 > array(boost::extents[size][size]);

		for (auto i = 0uz; i < size; ++i)
		{
			for (auto j = 0uz; j < size; ++j)
			{
				array[i][j] = j + 1;
			}
		}

		using range_t = boost::multi_array_types::index_range;

		auto view = array[boost::indices[range_t(0, 2)][range_t(0, 5, 2)]];

		assert(view[0][0] == 1 && view[0][1] == 3 && view[0][2] == 5);

		assert(view[1][0] == 1 && view[1][1] == 3 && view[1][2] == 5);
	}
}