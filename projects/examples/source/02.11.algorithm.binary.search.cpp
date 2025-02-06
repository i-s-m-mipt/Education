#include <cassert>
#include <numeric>
#include <vector>

/////////////////////////////////////////////////////////////////////

auto find(const std::vector < int > & vector, int x) -> bool
{
	if (std::size(vector) > 0)
	{
		auto left = 0uz, right = std::size(vector) - 1, middle = 0uz;

		while (left < right)
		{		
			middle = std::midpoint(left, right);

			vector[middle] < x ? left = middle + 1 : right = middle;
		}

		return vector[left] == x;
	}
	
	return 0;
}

/////////////////////////////////////////////////////////////////////

int main()
{
	assert(find({ 1, 2, 3, 4, 5 }, 1));
}