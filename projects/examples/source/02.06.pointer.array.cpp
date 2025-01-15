#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>

///////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		[[maybe_unused]] int array_1[5]{};

		[[maybe_unused]] int array_2[5]{ 1, 2, 3 }; 

		[[maybe_unused]] int array_3[]{ 1, 2, 3, 4, 5 };
	
//		[[maybe_unused]] int array_4[1'000'000'000]{}; // error

//		[[maybe_unused]] int array_5[0]{}; // error
	}
	
//  ---------------------------------------------------------------------------

	{
		int array[5]{ 1, 2, 3, 4, 5 };

//		assert(sizeof(array) / sizeof(array[0]) == 5); // bad

		assert(std::size(array) == 5);

		assert(*array == 1);

		assert(array[1] == *(array + 1) && array[1] == 1[array]);

//		*(array + 1'000) = 0; // error

		assert(array + std::size(array) - 1 - array == 4);

		for (auto ptr = array; ptr != array + std::size(array); ++ptr) 
		{
			assert(*ptr == (ptr == array ? 1 : *(ptr - 1) + 1));
		}
	}

//  ---------------------------------------------------------------------------

	{
		std::cout << "main : enter size : "; auto size = 0uz; std::cin >> size;

		int array[1'000]{}; assert(size < std::size(array));

		for (auto i = 0uz; i < size; ++i)
		{
			array[i] = i + 1;
		}

		assert(std::ranges::is_sorted(array, array + size));
	}
}