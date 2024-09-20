#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

int main()
{
	const std::size_t size = 5;

	[[maybe_unused]]       int array_1[size] {         };
	[[maybe_unused]] const int array_2[size] { 1, 2, 3 }; 
	[[maybe_unused]] const int array_3[    ] { 1, 2, 3 };
	
//	[[maybe_unused]] const int array_4[1'000'000'000] {}; // error

//  ================================================================================================

//	assert(sizeof(array_3) / sizeof(array_3[0]) == 3); // bad

	assert(std::size(array_3) == 3);

//  ================================================================================================

	*array_1 = 1;

	const auto middle = size / 2;

	*(array_1 + middle) = 3;

//	*(array_1 + 10'000) = 1; // error

	assert(array_1[middle] == 3);

//	assert(middle[array_1] == 3); // bad

	assert(array_1 + middle - array_1 == 2);

//	[[maybe_unused]] const auto delta = array_2 - array_1; // bad

	for (auto ptr = array_1; ptr != array_1 + size; ++ptr) *ptr = 1;

//  ================================================================================================

	std::cout << "Enter 1 unsigned integer: "; std::size_t n{}; std::cin >> n;

	int buffer[1000] {}; assert(n <= std::size(buffer));

	std::ranges::iota(buffer, buffer + n, 1);

	for (std::size_t i = 0; i < n - 1; ++i)
	{
		for (std::size_t j = i + 1; j < n; ++j)
		{
			if (buffer[i] < buffer[j]) std::swap(buffer[i], buffer[j]);
		}
	}

	assert(std::ranges::is_sorted(buffer, buffer + n, std::ranges::greater()));

	return 0;
}