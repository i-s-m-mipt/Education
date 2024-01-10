#include <iostream>
#include <utility>
#include <vector>

int main()
{
	std::cout << "Enter array size: "; std::size_t n{}; std::cin >> n;

	std::cout << "Enter " << n << " integer values: ";

	std::vector < int > v(n, 0); // note: create vector of n zero elements

	const auto size = v.size(); // note: get current vector size

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cin >> v[i]; // note: consider push_back as alternative
	}

	for (std::size_t i = 0; i < size - 1; ++i)
	{
		for (std::size_t j = i + 1; j < size; ++j)
		{
			if (v[i] > v[j])
			{
				std::swap(v[i], v[j]);
			}
		}
	}

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << v[i] << (i + 1 == size ? '\n' : ' ');
	}

	return 0;
}