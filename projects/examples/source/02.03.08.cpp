//////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 0uz;

//  ------------------------------------------------------------------
	
	std::cout << "main : enter std::size_t size : "; std::cin >> size;

//  ------------------------------------------------------------------

	std::vector < int > vector(size, 0);

//  ------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		vector[i] = i + 1;
	}

//  ------------------------------------------------------------------

	assert(std::ranges::is_sorted(vector));
}

//////////////////////////////////////////////////////////////////////