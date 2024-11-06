#include <cassert>
#include <numeric>
#include <vector>

//  ================================================================================================

[[nodiscard]] auto find(const std::vector < int > & vector, int key)
{
	auto result = false;

	if (auto size = std::size(vector); size > 0)
	{
		auto l = 0uz, r = size - 1, m = 0uz;

		while (l < r)
		{		
			vector[m = std::midpoint(l, r)] < key ? l = m + 1 : r = m;
		}

		result = vector[l] == key;
	}
	
	return result;
}

//  ================================================================================================

int main()
{
	assert(find({ 1, 2, 3, 4, 5 }, 1));
}