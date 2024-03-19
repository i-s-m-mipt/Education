#include <iostream>
#include <utility>
#include <vector>

int main()
{
	const std::size_t n = 5;

	std::vector < int > vector(n, 0); // note: create vector of n zero elements

	for (std::size_t i = 0; i < n; ++i) // note: see also std::size instead of n
	{
		vector[i] = static_cast < int > (n - i); // note: see also push_back
	}

	for (std::size_t i = 0; i < n - 1; ++i)
	{
		for (std::size_t j = i + 1; j < n; ++j)
		{
			if (vector[i] > vector[j])
			{
				std::swap(vector[i], vector[j]);
			}
		}
	}

	for (const auto element : vector) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}