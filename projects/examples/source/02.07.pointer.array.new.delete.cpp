#include <algorithm>
#include <cassert>
#include <numeric>
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

	const auto buffer = new int[size]; 

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

	delete[] buffer;

	return 0;
}