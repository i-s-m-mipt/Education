import std;

int main()
{
	const std::size_t size = 3;

	int a[size][size]
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

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

	auto line = new int[size * size]{};

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			line[i * size + j] = 42;
		}
	}

	delete[] line;

	return 0;
}