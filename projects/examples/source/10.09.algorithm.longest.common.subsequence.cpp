#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////

auto find(const std::vector < int > & vector_1, const std::vector < int > & vector_2) 
{
	std::vector < std::vector < std::size_t > > vector_3
	(
		std::size(vector_1) + 1, std::vector < std::size_t > 
		(
			std::size(vector_2) + 1, 0
		)
	);

	for (auto i = 1uz; i < std::size(vector_1) + 1; ++i)
	{
		for (auto j = 1uz; j < std::size(vector_2) + 1; ++j)
		{
			if (vector_1[i - 1] == vector_2[j - 1])
			{
				vector_3[i][j] = vector_3[i - 1][j - 1] + 1;
			}
			else
			{
				vector_3[i][j] = std::max(vector_3[i - 1][j], vector_3[i][j - 1]);
			}
		}
	}

	std::vector < int > result;

	auto i = std::ssize(vector_1) - 1, j = std::ssize(vector_2) - 1;

	while (i >= 0 && j >= 0)
	{
		if (vector_1[i] == vector_2[j])
		{
			result.push_back(vector_1[i]); --i; --j;
		}
		else 
		{
			vector_3[i][j + 1] > vector_3[i + 1][j] ? --i : --j;
		}
	}

	std::ranges::reverse(result);
	
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
	assert(find({ 1, 2, 3, 4, 5 }, { 1, 2, 3 }) == std::vector < int > ({ 1, 2, 3 }));
}