#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>

///////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto object = new auto(1);  

		assert(*object == 1);
	
		delete object;
	}
	
//  ---------------------------------------------------------------------------

	{
		auto array = new int[5]{};

		assert(array[0] == 0);

		delete[] array;

//		delete array; // error
	}

//  ---------------------------------------------------------------------------

	{
		std::cout << "main : enter size : "; auto size = 0uz; std::cin >> size;

		auto array = new int[size]; 

		for (auto i = 0uz; i < size; ++i)
		{
			array[i] = i + 1;
		}

		assert(std::ranges::is_sorted(array, array + size));

		delete[] array;
	}	
}