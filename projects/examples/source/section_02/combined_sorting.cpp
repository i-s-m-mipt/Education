#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

void insertion_sort(std::vector < int > & v, int left, int right)
{
	for (auto i = left + 1; i < right; ++i)
	{
		for (auto j = i; j > left; --j)
		{
			if (v[j - 1] > v[j])
			{
				std::swap(v[j], v[j - 1]);
			}
		}
	}
}

void merge(std::vector < int > & v, std::size_t left, std::size_t middle, std::size_t right)
{
	const auto begin = left;

	std::vector < int > tmp_v(right - left, 0);

	const auto size = tmp_v.size();

	for (std::size_t i = 0, end = middle; i < size; ++i)
	{
		if (left < end && middle < right && v[left] <= v[middle])
		{
			tmp_v[i] = v[left++];
		} 
		else if (left < end && middle < right)
		{
			tmp_v[i] = v[middle++];
		}
		else if (left < end)
		{
			tmp_v[i] = v[left++];
		}
		else
		{
			tmp_v[i] = v[middle++];
		}
	}

	for (std::size_t i = 0; i < size; ++i)
	{
		v[begin + i] = tmp_v[i];
	}
}

void merge_sort(std::vector < int > & v, std::size_t left, std::size_t right)
{
	if (static const std::size_t block_size = 64; right - left <= block_size)
	{
		insertion_sort(v, left, right); // good: amortized complexity as in std::sort
	}
	else
	{
		auto middle = std::midpoint(left, right); // good: optimized for overflows

		merge_sort(v, left,   middle);
		merge_sort(v, middle, right );

		merge(v, left, middle, right);
	}
}

int main()
{
	std::cout << "Enter array size: ";

	std::size_t n{};

	std::cin >> n;

	std::vector < int > v(n, 0);

	const auto size = v.size();

	for (std::size_t i = 0; i < size; ++i)
	{
		v[i] = size - i;
	}

	merge_sort(v, 0, size); // note: half-open interval

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << v[i] << (i + 1 == size ? '\n' : ' ');
	}

	return 0;
}