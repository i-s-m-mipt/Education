#include <array>
#include <iomanip>
#include <iostream>
#include <vector>

#include <boost/multi_array.hpp>

//  ================================================================================================

template < typename T, std::size_t S > class Array_2D 
{
public:

	class Row 
	{
	public:

		explicit Row(T * array) : m_array(array) {}

//      --------------------------------------------------

		[[nodiscard]] auto & operator[](std::size_t index)
		{ 
			return m_array[index]; 
		}

	private:

		T * m_array = nullptr;
	};

//  ------------------------------------------------------

	[[nodiscard]] auto operator[](std::size_t index)
	{ 
		return Row(m_array[index]); 
	}

private:

	T m_array[S][S]{};
};

//  ================================================================================================

int main()
{
	const auto size = 5uz;

//  ================================================================================================

	[[maybe_unused]] int array_2D_v1[size][size]{};

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_2D_v1[i][j] = 1;
		}
	}

//  ================================================================================================

	Array_2D < int, size > array_2D_v2;

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_2D_v2[i][j] = 42;
		}
	}

//  ================================================================================================

	auto array_2D_v3 = new int*[size]{};

	for (auto i = 0uz; i < size; ++i)
	{
		array_2D_v3[i] = new int[size]{};
	}

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_2D_v3[i][j] = 42;
		}
	}

	for (auto i = 0uz; i < size; ++i)
	{
		delete[] array_2D_v3[i];
	}

	delete[] array_2D_v3;

//  ================================================================================================

	auto array_2D_v4 = new int[size * size]{};

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_2D_v4[i * size + j] = 42;
		}
	}

	delete[] array_2D_v4;

//  ================================================================================================

	std::array < std::array < int, size > , size > array_2D_v5;

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_2D_v5[i][j] = 42;
		}
	}

//  ================================================================================================

	std::vector < std::vector < int > > array_2D_v6(size, std::vector < int > (size, 0));

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array_2D_v6[i][j] = 42;
		}
	}

//  ================================================================================================

	auto size_1 = 3uz;
	auto size_2 = 4uz;
	auto size_3 = 5uz;

	boost::multi_array < int, 3 > array_2D_v7(boost::extents[size_1][size_2][size_3]);

	auto index = 0;

	for (auto i = 0uz; i < size_1; ++i)
	{
		for (auto j = 0uz; j < size_2; ++j)
		{
			for (auto k = 0uz; k < size_3; ++k)
			{
				std::cout << std::setw(2) << std::setfill(' ') << std::right;
				
				std::cout << (array_2D_v7[i][j][k] = ++index) << ' ';
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

//  ================================================================================================

	using range_t = boost::multi_array_types::index_range;

	auto view = array_2D_v7[boost::indices[range_t(0, 2)][1][range_t(0, 5, 2)]];

	auto view_size_1 = 2uz;
	auto view_size_2 = 3uz;

	for (auto i = 0uz; i < view_size_1; ++i)
	{
		for (auto k = 0uz; k < view_size_2; ++k)
		{
			std::cout << std::setw(2) << std::setfill(' ') << std::right << view[i][k] << ' ';
		}

		std::cout << std::endl;
	}
}