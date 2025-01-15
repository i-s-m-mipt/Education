#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "main : enter size : "; auto size = 0uz; std::cin >> size;

	std::vector < int > vector(size, 0);

	for (auto i = 0uz; i < std::size(vector); ++i)
	{
		vector[i] = i + 1;
	}

	assert(std::ranges::is_sorted(vector));
}