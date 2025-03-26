#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/DPLCS.html

//////////////////////////////////////////////////////////////////////////////////////

auto find(const std::vector < int > & vector_1, const std::vector < int > & vector_2) 
{
	auto size_1 = std::size(vector_1);

	auto size_2 = std::size(vector_2);

	std::vector < std::vector < std::size_t > > buffer_1
	(
		size_1 + 1, std::vector < std::size_t > 
		(
			size_2 + 1, 0
		)
	);

	for (auto i = 1uz; i < size_1 + 1; ++i)
	{
		for (auto j = 1uz; j < size_2 + 1; ++j)
		{
			if (vector_1[i - 1] == vector_2[j - 1])
			{
				buffer_1[i][j] = buffer_1[i - 1][j - 1] + 1;
			}
			else
			{
				buffer_1[i][j] = std::max(buffer_1[i - 1][j], buffer_1[i][j - 1]);
			}
		}
	}

//  ------------------------------------------------------------------------------

	std::vector < int > buffer_2;

	auto i = std::ssize(vector_1) - 1, j = std::ssize(vector_2) - 1;

	while (i >= 0 && j >= 0)
	{
		if (vector_1[i] == vector_2[j])
		{
			buffer_2.push_back(vector_1[i]);
			
			--i;
			
			--j;
		}
		else 
		{
			buffer_1[i][j + 1] > buffer_1[i + 1][j] ? --i : --j;
		}
	}

	std::ranges::reverse(buffer_2);
	
	return buffer_2;
}

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
	assert(find({ 1, 2, 3, 4, 5 }, { 1, 2, 3 }) == std::vector < int > ({ 1, 2, 3 }));
}