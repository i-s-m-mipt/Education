#include <array>
#include <cstddef>
#include <vector>

#include <boost/multi_array.hpp>

/////////////////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t S > class Array
{
public:

	class Row 
	{
	public:

		Row(T * array) : m_array(array) {}

	//  -------------------------------------------

		auto & operator[](std::size_t index)
		{ 
			return m_array[index]; 
		}

	private:

		T * m_array = nullptr;
	};

//  -----------------------------------------------

	auto operator[](std::size_t index)
	{ 
		return Row(m_array[index]); 
	}

private:

	T m_array[S][S]{};
};

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	constexpr auto size = 5uz;

//  -------------------------------------------------------------------------------------

	[[maybe_unused]] int array_1[size][size]{};

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_1[i][j] = 1;
		}
	}

//  -------------------------------------------------------------------------------------

	Array < int, size > array_2;

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_2[i][j] = 1;
		}
	}

//  -------------------------------------------------------------------------------------

	auto array_3 = new int*[size]{};

	for (auto i = 0uz; i < size; ++i)
	{
		array_3[i] = new int[size]{};
	}

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_3[i][j] = 1;
		}
	}

	for (auto i = 0uz; i < size; ++i)
	{
		delete[] array_3[i];
	}

	delete[] array_3;

//  -------------------------------------------------------------------------------------

	auto array_4 = new int[size * size]{};

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_4[i * size + j] = 1;
		}
	}

	delete[] array_4;

//  -------------------------------------------------------------------------------------

	std::array < std::array < int, size > , size > array_5;

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_5[i][j] = 1;
		}
	}

//  -------------------------------------------------------------------------------------

	std::vector < std::vector < int > > vector(size, 
				  std::vector < int > 		  (size, 0));

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			vector[i][j] = 1;
		}
	}

//  -------------------------------------------------------------------------------------

	auto size_1 = 3uz;
	auto size_2 = 4uz;
	auto size_3 = 5uz;

	boost::multi_array < int, 3 > array_6(boost::extents[size_1][size_2][size_3]);

	for (auto i = 0uz; i < size_1; ++i)
	{
		for (auto j = 0uz; j < size_2; ++j)
		{
			for (auto k = 0uz; k < size_3; ++k)
			{
				array_6[i][j][k] = 1;
			}
		}
	}

//  -------------------------------------------------------------------------------------

	using range_t = boost::multi_array_types::index_range;

	auto view = array_6[boost::indices[range_t(0, 2)][1][range_t(0, 5, 2)]];

	assert(view[0][0] == 1 && view[0][1] == 1 && view[0][2] == 1);
	assert(view[1][0] == 1 && view[1][1] == 1 && view[1][2] == 1);
}