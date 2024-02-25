#include <iostream>
#include <utility>
#include <vector>

int main()
{
	std::cout << "Enter array size: "; std::size_t n{}; std::cin >> n;

	std::cout << "Enter " << n << " integer values: ";

	std::vector < int > vector(n, 0); // note: create vector of n zero elements

	for (auto & element : vector) std::cin >> element; // note: consider push_back

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

	for (auto element : vector) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}