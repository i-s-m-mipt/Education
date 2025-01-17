#include <cassert>
#include <numeric>
#include <vector>

//////////////////////////////////////////////////////////////////////

auto find(const std::vector < int > & vector, int key)
{
	if (std::size(vector) > 0)
	{
		auto l = 0uz, r = std::size(vector) - 1, m = 0uz;

		while (l < r)
		{		
			vector[m = std::midpoint(l, r)] < key ? l = m + 1 : r = m;
		}

		return vector[l] == key;
	}
	
	return false;
}

//////////////////////////////////////////////////////////////////////

int main()
{
	assert(find({ 1, 2, 3, 4, 5 }, 1));
}