#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

void insertion_sort(std::vector < int > & v, std::size_t l, std::size_t r) // note: O(N^2) complexity 
{
	for (auto i = l + 1; i < r; ++i)
	{
		for (auto j = i; j > l; --j)
		{
			if (v[j - 1] > v[j]) 
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

	for (auto & e : t) 
	{
		e = v[((l < end && ((m < r && v[l] <= v[m]) || (m == r))) ? l++ : m++)];
	}

	for (std::size_t i = 0; i < std::size(t); ++i) v[begin + i] = t[i];
}

void merge_sort(std::vector < int > & v, std::size_t l, std::size_t r) // note: O(N*log(N)) complexity (amortized)
{
	if (static const std::size_t block = 64; r - l <= block)
	{
		insertion_sort(v, l, r); // good: double nested loop instead of recursive calls
	}
	else
	{
		auto m = std::midpoint(l, r); 
		
		merge_sort(v, l, m   );
		merge_sort(v,    m, r);
		merge_sort(v, l, m, r);
	}
}

int main()
{
	std::cout << "Enter array size: "; std::size_t n{}; std::cin >> n;

	std::vector < int > vector(n, 0);

	for (auto value = static_cast < int > (n); auto & element : vector) element = value--;

	merge_sort(vector, 0, n); // good: half-open intervals preferred in C++

	for (auto element : vector) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}