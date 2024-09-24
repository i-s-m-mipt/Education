#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>

int main()
{
	const auto object = new int{};  

	*object = 1; assert(*object == 1);
	
	delete object;

//  ================================================================================================

	const std::size_t size = 5;

	const auto array = new int[size] {};

	array[0] = 1; assert(array[0] == 1);

//	delete array; // error

	delete[] array;

//  ================================================================================================

	std::cout << "Enter 1 unsigned integer : "; std::size_t n{}; std::cin >> n;

	const auto buffer = new int[n]; 

	std::ranges::iota(buffer, buffer + n, 1);

	for (std::size_t i = 0; i < n - 1; ++i)
	{
		for (std::size_t j = i + 1; j < n; ++j)
		{
			if (buffer[i] < buffer[j]) std::swap(buffer[i], buffer[j]);
		}
	}

	assert(std::ranges::is_sorted(buffer, buffer + n, std::ranges::greater()));

	delete[] buffer;

	return 0;
}