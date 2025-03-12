int main()
{
    constexpr auto size = 5uz;

//  -----------------------------------------

	[[maybe_unused]] int array[size][size]{};

//  -----------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			array[i][j] = j + 1;
		}
	}
}