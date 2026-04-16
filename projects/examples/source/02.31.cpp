////////////////////////////////////////////////////////

// chapter : Functions

////////////////////////////////////////////////////////

// section : Memory

////////////////////////////////////////////////////////

// content : Container std::vector
//
// content : Capacity and Size
//
// content : Back Insertion Algorithm
//
// content : Time Complexities O(1) and O(N)
//
// content : Amortized Time Complexity
//
// content : Algorithm std::ranges::sort
//
// content : Functor std::less
//
// content : Algorithm std::ranges::is_sorted

////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector = { 5, 4, 3, 2, 1 };

//  ----------------------------------------------------

	vector.push_back(1);

//  ----------------------------------------------------

	std::ranges::sort(vector, std::less());

//  ----------------------------------------------------

	assert(std::ranges::is_sorted(vector, std::less()));
}

////////////////////////////////////////////////////////