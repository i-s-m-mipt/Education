#include <cassert>
#include <numeric>
#include <vector>

////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/Search.html

////////////////////////////////////////////////////////////////////

auto find(const std::vector < int > & vector, int x)
{
	if (auto size = std::size(vector); size > 0)
	{
		auto left = 0uz, right = size - 1, middle = 0uz;

		while (left < right)
		{		
			middle = std::midpoint(left, right);

			vector[middle] < x ? left = middle + 1 : right = middle;
		}

		return vector[left] == x;
	}
	
	return false;
}

////////////////////////////////////////////////////////////////////

int main()
{
	assert(find({ 1, 2, 3, 4, 5 }, 1));
}