#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

int main()
{
	std::cout << "Enter 1 unsigned integer : "; std::size_t n{}; std::cin >> n;

	std::vector < int > vector(n, 0);

	std::ranges::iota(vector, 1);

	for (std::size_t i = 0; i < n - 1; ++i)
	{
		for (std::size_t j = i + 1; j < n; ++j)
		{
			if (vector[i] < vector[j]) std::swap(vector[i], vector[j]);
		}
	}

	assert(std::ranges::is_sorted(vector, std::ranges::greater()));

	return 0;
}