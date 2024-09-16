#include <algorithm>
#include <cassert>
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

//	assert(*(&array_1[0] + middle) == 3); // bad

//	assert(middle[array_1] == 3); // bad

	assert((array_1 + middle + 1) - (array_1 + middle - 1) == 2);

//	[[maybe_unused]] auto delta = array_2 - array_1; // bad

	for (int * ptr = array_1; ptr != (array_1 + size); ++ptr) *ptr = 1;

//  ================================================================================================

	const std::size_t buffer_size = 1024;

	int buffer[buffer_size] {};

	std::iota(buffer, buffer + size, 1);

	for (std::size_t i = 0; i < size - 1; ++i)
	{
		for (std::size_t j = i + 1; j < size; ++j)
		{
			if (buffer[i] < buffer[j]) 
			{
				std::swap(buffer[i], buffer[j]);
			}
		}
	}

	assert
	(
		buffer[0] == 5 && 
 	    buffer[1] == 4 && 
	    buffer[2] == 3 && 
	    buffer[3] == 2 && 
	    buffer[4] == 1
	);

	return 0;
}