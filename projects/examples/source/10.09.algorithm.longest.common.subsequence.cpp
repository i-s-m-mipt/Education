#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

template < typename T > [[nodiscard]] constexpr std::vector < T > longest_common_subsequence(
	const std::vector < T > & sequence_1, 
	const std::vector < T > & sequence_2) 
{
	std::vector < std::vector < int > > table(std::size(sequence_1) + 1, 
                  std::vector < int >        (std::size(sequence_2) + 1, 0)); // note: dynamic programming

	for (std::size_t i = 1; i < std::size(sequence_1) + 1; ++i)
	{
		for (std::size_t j = 1; j < std::size(sequence_2) + 1; ++j)
		{
			if (sequence_1[i - 1] == sequence_2[j - 1])
			{
				table[i][j] = table[i - 1][j - 1] + 1;
			}
			else
			{
				table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
			}
		}
	}

	std::vector < T > result; result.reserve(std::min(std::size(sequence_1), std::size(sequence_2)));

	for (int i = std::size(sequence_1) - 1, j = std::size(sequence_2) - 1; i >= 0 && j >= 0; )
	{
		if (sequence_1[i] == sequence_2[j])
		{
			result.push_back(sequence_1[i]); --i; --j;
		}
		else (table[i][j + 1] > table[i + 1][j] ? --i : --j);
	}

	std::ranges::reverse(result); // note: reverse range
	
	return result;
}

int main()
{

	const std::vector < int > sequence_1 = { 1, 2, 2, 3, 4, 4 };
	const std::vector < int > sequence_2 = { 1, 1, 2, 3, 3, 4 };

	for (const auto element : longest_common_subsequence(sequence_1, sequence_2))
	{
		std::cout << element << ' ';
	}

	std::cout << std::endl;

	return 0;
}