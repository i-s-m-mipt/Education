#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>

int main()
{
	[[maybe_unused]] int array_1[5]{};

	[[maybe_unused]] int array_2[5]{ 1, 2, 3 }; 

	[[maybe_unused]] int array_3[]{ 1, 2, 3, 4, 5 };
	
//	[[maybe_unused]] int array_4[1'000'000'000]{}; // error

//	[[maybe_unused]] int array_5[0]{}; // error

//  ------------------------------------------------------------------------------------------------

//	assert(sizeof(array_1) / sizeof(array_1[0]) == 5); // bad

	assert(std::size(array_1) == 5);

//  ------------------------------------------------------------------------------------------------

	*array_1 = 1;

	auto middle = std::size(array_1) / 2;

	*(array_1 + middle) = 3;
//	*(array_1 - middle) = 3; // error

	assert(array_1[middle] == 3);

//	assert(middle[array_1] == 3); // bad

	assert(array_1 + middle - array_1 == 2);

//	[[maybe_unused]] auto delta = array_2 - array_1; // bad

	for (auto ptr = array_1; ptr != array_1 + std::size(array_1); ++ptr) 
	{
		*ptr = 0;
	}

//  ------------------------------------------------------------------------------------------------

	auto size = 5uz; int buffer[1'000]{};

	for (auto i = size; i > 0; --i)
	{
		buffer[size - i] = static_cast < int > (i);
	}

//  ------------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size - 1; ++i)
	{
		for (auto j = i + 1; j < size; ++j)
		{
			if (buffer[i] > buffer[j]) 
			{
				std::swap(buffer[i], buffer[j]);
			}
		}
	}

//  ------------------------------------------------------------------------------------------------

	assert(std::ranges::is_sorted(buffer, buffer + size));
}