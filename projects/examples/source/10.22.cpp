/////////////////////////////////////////////

// chapter : Storage

/////////////////////////////////////////////

// section : Nested Containers

/////////////////////////////////////////////

// content : Nested Containers
//
// content : Nested Static Arrays

/////////////////////////////////////////////

int main()
{
    auto const size = 5uz;

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

/////////////////////////////////////////////