#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template < typename T > std::vector < T > longest_common_subsequence(const std::vector < T > & s1, const std::vector < T > & s2) 
{
	std::vector < std::vector < int > > table(std::size(s1) + 1, 
                  std::vector < int >        (std::size(s2) + 1, 0)); // note: dynamic programming

	for (std::size_t i = 1; i < std::size(s1) + 1; ++i)
	{
		for (std::size_t j = 1; j < std::size(s2) + 1; ++j)
		{
			table[i][j] = (s1[i - 1] == s2[j - 1] ? table[i - 1][j - 1] + 1 : std::max(table[i - 1][j], table[i][j - 1]));
		}
	}

	std::vector < T > result; result.reserve(std::min(std::size(s1), std::size(s2)));

	for (int i = std::size(s1) - 1, j = std::size(s2) - 1; i >= 0 && j >= 0; )
	{
		if (s1[i] == s2[j])
		{
			result.push_back(s1[i]); --i; --j;
		}
		else (table[i][j + 1] > table[i + 1][j] ? --i : --j);
	}

	std::ranges::reverse(result); return result;
}

int main()
{

	std::vector < int > sequence_1 = { 1, 2, 2, 3, 4, 4 };
	std::vector < int > sequence_2 = { 1, 1, 2, 3, 3, 4 };

	for (auto element : longest_common_subsequence(sequence_1, sequence_2))
	{
		std::cout << element << ' '; // note: outputs 1 2 3 4
	}

	std::cout << std::endl;

	return 0;
}