#include <iostream>
#include <numeric>

//  ================================================================================================

[[nodiscard]] const int * binary_search(const int * array, std::size_t size, int key) // complexity: O(log(N))
{
	if (std::size_t l = 0, r = size; r != 0)
	{
		while (l < r)
		{
			const auto m = std::midpoint(l, r); array[m] < key ? l = m + 1 : r = m;
		}

		return (array[l] == key ? array + l : nullptr);
	} 
	else return nullptr;
}

//  ================================================================================================

int main()
{
	const int array[]{1, 3, 4, 5, 6, 7, 8 };

	const std::size_t size = std::size(array);

	for (auto key = array[0] - 1; key <= array[size - 1] + 1; ++key)
	{
		std::cout << "Index of element " << key << " in array: ";

		if (const auto ptr = binary_search(array, size, key); ptr)
		{
			std::cout << ptr - array << std::endl;
		}
		else
		{
			std::cout << "not found" << std::endl;
		}
	}

	return 0;
}