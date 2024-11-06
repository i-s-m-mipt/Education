#include <algorithm>
#include <cassert>
#include <cmath>
#include <iterator>
#include <vector>

//  ================================================================================================

auto find(const std::vector < int > & vector_1, const std::vector < int > & vector_2) 
{
	std::vector < std::vector < std::size_t > > table(std::size(vector_1) + 1, 
                  std::vector < std::size_t >        (std::size(vector_2) + 1, 0));

	for (auto i = 1uz; i < std::size(vector_1) + 1; ++i)
	{
		for (auto j = 1uz; j < std::size(vector_2) + 1; ++j)
		{
			if (vector_1[i - 1] == vector_2[j - 1])
			{
				table[i][j] = table[i - 1][j - 1] + 1;
			}
			else
			{
				table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
			}
		}
	}

	std::vector < int > result;

	for (int i = std::size(vector_1) - 1, j = std::size(vector_2) - 1; i >= 0 && j >= 0; )
	{
		if (vector_1[i] == vector_2[j])
		{
			result.push_back(vector_1[i]); --i; --j;
		}
		else 
		{
			table[i][j + 1] > table[i + 1][j] ? --i : --j;
		}
	}

	std::ranges::reverse(result);
	
	return result;
}

//  ================================================================================================

int main()
{
	assert((find({ 1, 2, 3, 4, 5 }, { 1, 2, 3 }) == std::vector < int > { 1, 2, 3 }));
}