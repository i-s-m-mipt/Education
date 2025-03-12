int main()
{
    auto size = 5uz;

//  -------------------------------------

	auto array = new int[size * size]{};

//  -------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array[i * size + j] = j + 1;
		}
	}

//  -------------------------------------

	delete[] array;
}