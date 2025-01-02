#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>

int main()
{
	auto object = new auto(1);  

	*object = 2; assert(*object == 2);
	
	delete object;

//  ------------------------------------------------------------------------------------------------

	auto array = new int[5]{};

	array[0] = 1; assert(array[0] == 1);

	delete[] array;

//	delete array; // error

//  ------------------------------------------------------------------------------------------------

	auto size = 5uz; 
	
	auto buffer = new int[size]; 

	for (auto i = size; auto & element : std::ranges::subrange(buffer, buffer + size))
    {
        element = i--;
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

//  ------------------------------------------------------------------------------------------------

	delete[] buffer;
}