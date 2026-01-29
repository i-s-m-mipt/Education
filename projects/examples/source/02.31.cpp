////////////////////////////////////////////////////////

// chapter : Basics of Programming

////////////////////////////////////////////////////////

// section : Collections and Containers

////////////////////////////////////////////////////////

// content : Container std::vector
//
// content : Algorithmic Complexities O(1) and O(N)
//
// content : Algorithm std::ranges::is_sorted
//
// content : Function Object std::less

////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ----------------------------------------------------

	vector.push_back(vector.back() + 1);

//  ----------------------------------------------------

	assert(std::ranges::is_sorted(vector, std::less()));
}

////////////////////////////////////////////////////////