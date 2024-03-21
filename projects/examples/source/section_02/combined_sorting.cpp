#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

void insertion_sort(std::vector < int > & v, std::size_t l, std::size_t r) // note: O(N^2) complexity 
{
	for (auto i = l + 1; i < r; ++i)
	{
		for (auto j = i; j > l; --j)
		{
			if (v[j - 1] > v[j]) // note: sort in ascending order
			{
				std::swap(v[j], v[j - 1]);
			}
		}
	}
}

void merge_sort(std::vector < int > & v, std::size_t l, std::size_t m, std::size_t r)
{
	const auto begin = l, end = m;

	std::vector < int > t(r - l, 0); // note: one additional container instead of two

	for (auto & e : t) e = v[((l < end && ((m < r && v[l] <= v[m]) || (m == r))) ? l++ : m++)];

	for (std::size_t i = 0; auto e : t) v[begin + (i++)] = e;
}

void merge_sort(std::vector < int > & v, std::size_t l, std::size_t r) // note: O(N*log(N)) complexity (amortized)
{
	if (static const std::size_t block = 64; r - l <= block)
	{
		insertion_sort(v, l, r); // good: double nested loop instead of recursive calls
	}
	else
	{
		const auto m = std::midpoint(l, r); 
		
		merge_sort(v, l, m   );
		merge_sort(v,    m, r);
		merge_sort(v, l, m, r);
	}
}

int main()
{
	const std::size_t n = 128;

	std::vector < int > vector(n, 0);

	std::iota(std::begin(vector), std::end(vector), 1); // note: generate range 1, 2, 3, ...

	std::ranges::reverse(vector); // note: reverse range

	merge_sort(vector, 0, n); // good: half-open intervals preferred in C++

	for (const auto element : vector) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}