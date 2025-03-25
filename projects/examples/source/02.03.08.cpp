#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////

int main()
{
	auto size = 0uz;
	
	std::cout << "main : enter size : "; std::cin >> size;

	std::vector < int > vector(size, 0);

	for (auto i = 0uz; i < std::size(vector); ++i)
	{
		vector[i] = i + 1;
	}

	assert(std::ranges::is_sorted(vector));
}