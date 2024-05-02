#include <iostream>
#include <numeric>

//  ================================================================================================

[[nodiscard]] const int * binary_search(const int * array, std::size_t size, int key) 
{
	std::size_t l = 0, r = size;

	if (r == 0)
	{
		return nullptr; // good: nullptr is better than index value like INT_MAX or -1
	}

	if (r == 1)
	{
		return (array[0] == key ? array : nullptr);
	}

	while (l < r) // good: O(log(N)) complexity, selection with only 2 branches
	{
		const auto m = std::midpoint(l, r); array[m] < key ? l = m + 1 : r = m;
	}

	return (array[l] == key ? &array[l] : nullptr); // good: one additional comparison after the loop
}

//  ================================================================================================

int main()
{
	const int array[]{1, 3, 4, 5, 6, 7, 8 }; // note: sorted array, consider std::vector with iterators

	const std::size_t size = std::size(array);

	for (auto key = array[0] - 1; key <= array[size - 1] + 1; ++key)
	{
		std::cout << "index of " << key << " in array: ";

		if (const auto ptr = binary_search(array, size, key); ptr) // good: half-open interval
		{
			std::cout << ptr - array << std::endl; // note: get index through pointer arithmetic
		}
		else
		{
			std::cout << "not found" << std::endl;
		}
	}

	return 0;
}