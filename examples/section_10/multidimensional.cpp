#include <vector>

template < auto N > class Array_2D 
{
public:

	class Line 
	{
	public:

		explicit Line(int * array) noexcept : m_array(array) {}

		int & operator[](std::size_t index) noexcept
		{
			return m_array[index];
		}

	private:

		int * m_array;

	}; // class Line 

	auto operator[](std::size_t index) noexcept
	{
		return Line(m_array[index]);
	}

private:

	int m_array[N][N];

}; // template < auto N > class Array_2D

int main()
{
	const std::size_t size = 3;

	int a[size][size]
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	Array_2D < size > b;

	b[0][0] = 42; // note: proxy object

	auto p = new int*[size]{};

	for (std::size_t i = 0; i < size; ++i)
	{
		p[i] = new int[size]{};
	}

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			p[i][j] = 42;
		}
	}

	for (std::size_t i = 0; i < size; ++i)
	{
		delete[] p[i];
	}

	delete[] p;

	auto line = new int[size * size]{}; // note: can be more effective

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			line[i * size + j] = 42;
		}
	}

	delete[] line;

	std::vector < std::vector < int > > v(size, std::vector < int > (size));

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			v[i][j] = 42;
		}
	}

	return 0;
}