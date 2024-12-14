#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>

int main()
{
	auto object = new auto(0);  

	*object = 1; assert(*object == 1);
	
	delete object;

//  ------------------------------------------------------------------------------------------------

	auto array = new int[5]{};

	array[0] = 1; assert(array[0] == 1);

	delete[] array;

//	delete array; // error

//  ------------------------------------------------------------------------------------------------

	std::cout << "Enter 1 unsigned integer : "; std::size_t n; std::cin >> n;

	auto buffer = new int[n]; 

	std::ranges::iota(buffer, buffer + n, 1);

//  ------------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < n - 1; ++i)
	{
		for (auto j = i + 1; j < n; ++j)
		{
			if (buffer[i] < buffer[j]) 
			{
				std::swap(buffer[i], buffer[j]);
			}
		}
	}

//  ------------------------------------------------------------------------------------------------	

	assert(std::ranges::is_sorted(buffer, buffer + n, std::ranges::greater()));

//  ------------------------------------------------------------------------------------------------

	delete[] buffer;
}