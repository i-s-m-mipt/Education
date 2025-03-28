//////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iostream>

//////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 0uz;

//  ------------------------------------------------------------------
	
	std::cout << "main : enter std::size_t size : "; std::cin >> size;

//  ------------------------------------------------------------------

	auto array = new int[size]{};

//  ------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		array[i] = i + 1;
	}

//  ------------------------------------------------------------------

	assert(std::ranges::is_sorted(array, array + size));

//  ------------------------------------------------------------------

	delete[] array;
}

//////////////////////////////////////////////////////////////////////