#include <cassert>
#include <iterator>
#include <numeric>

//  ================================================================================================

[[nodiscard]] const int * binary_search(const int * array, std::size_t size, int key)
{
	if (size == 0) return nullptr;

	if (size == 1) return (array[0] == key ? array : nullptr);

	std::size_t left = 0, right = size - 1;

	while (left < right)
	{
		const auto middle = std::midpoint(left, right); 
		
		array[middle] < key ? left = middle + 1 : right = middle;
	}

	return (array[left] == key ? array + left : nullptr);
}

//  ================================================================================================

int main()
{
	const int array[] {1, 3, 4, 5, 6, 7, 8 };

	const auto size = std::size(array);

	assert(binary_search(array, size, 0) == nullptr  );
	assert(binary_search(array, size, 1) == array + 0);
	assert(binary_search(array, size, 2) == nullptr  );
	assert(binary_search(array, size, 3) == array + 1);
	assert(binary_search(array, size, 4) == array + 2);
	assert(binary_search(array, size, 5) == array + 3);
	assert(binary_search(array, size, 6) == array + 4);
	assert(binary_search(array, size, 7) == array + 5);
	assert(binary_search(array, size, 8) == array + 6);
	assert(binary_search(array, size, 9) == nullptr  );

	return 0;
}