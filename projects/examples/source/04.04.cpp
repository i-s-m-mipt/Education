////////////////////////////////////////////////////////

// chapter : Generic Programming

////////////////////////////////////////////////////////

// section : Function Templates

////////////////////////////////////////////////////////

// content : Non-Type Template Parameters
//
// content : Function max
//
// content : Passing Static Arrays by Lvalue Reference

////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <cstddef>

////////////////////////////////////////////////////////

template
< 
	typename T, std::size_t S1, std::size_t S2
> 
auto max(T const (&array_1)[S1], T const (&array_2)[S2])
{
	for (auto i = 0uz; i < std::min(S1, S2); ++i)
	{
		if (array_1[i] > array_2[i]) { return array_1; }

		if (array_1[i] < array_2[i]) { return array_2; }
	}

	return S1 > S2 ? array_1 : array_2;
}

////////////////////////////////////////////////////////

int main()
{
	int array_1[5]{ 1, 2, 3, 4, 5 };

	int array_2[5]{ 1, 2, 3 };

//  -----------------------------------------

	assert(max(array_1, array_2) == array_1);
}

////////////////////////////////////////////////////////