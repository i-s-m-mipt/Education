#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>

///////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "main : enter size : "; auto size = 0uz; std::cin >> size;

	int array[1'000]{};

	for (auto i = 0uz; i < size; ++i)
	{
		array[i] = i + 1;
	}

	assert(std::ranges::is_sorted(array, array + size));
}