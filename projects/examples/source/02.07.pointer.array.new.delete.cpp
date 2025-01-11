#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>

////////////////////////////////////////////////////////////

int main()
{
	{
		auto object = new auto(1);  

		assert(*object == 1);
	
		delete object;
	}
	
//  ========================================================

	{
		auto array = new int[5]{};

		assert(array[0] == 0);

		delete[] array;

//		delete array; // error
	}

//  ========================================================

	{
		auto size = 5uz; auto array = new int[size]; 

		for (auto i = 0uz; i < size; ++i)
		{
			array[i] = size - i;
		}

		for (auto i = 0uz; i < size - 1; ++i)
		{
			for (auto j = i + 1; j < size; ++j)
			{
				if (array[i] > array[j]) 
				{
					std::swap(array[i], array[j]);
				}
			}
		}

		assert(std::ranges::is_sorted(array, array + size));

		delete[] array;
	}	
}