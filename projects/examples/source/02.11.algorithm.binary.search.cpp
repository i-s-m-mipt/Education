#include <iostream>
#include <numeric>

[[nodiscard]] const int * find(const int * a, std::size_t l, std::size_t r, int k) // note: O(log(N)) complexity
{
	if (l >= r)
	{
		return nullptr; // good: nullptr is better than special index value like INT_MAX or -1
	}

	if (r - l == 1)
	{
		return (a[l] == k ? a : nullptr);
	}

	while (l < r) // good: one comparison in selection condition with two branches in the loop
	{
		if (auto middle = std::midpoint(l, r); a[middle] < k) // good: optimized for overflows
		{
			l = middle + 1;
		}
		else
		{
			r = middle;
		}
	}

	return (a[l] == k ? &a[l] : nullptr); // good: one additional comparison after the loop
}

int main()
{
	const int array[]{1, 3, 4, 5, 6, 7, 8 }; // note: sorted array, consider std::vector with iterators

	const std::size_t n = sizeof(array) / sizeof(int); // note: prefer std::size over this way

	for (auto i = array[0] - 1; i <= array[n - 1] + 1; ++i)
	{
		std::cout << "index of " << i << " in array: ";

		if (const auto ptr = find(array, 0, n, i); ptr) // good: half-open intervals preferred in C++
		{
			std::cout << ptr - array << std::endl; // note: get index through pointer arithmetic
		}
		else
		{
			std::cout << "not found" << std::endl;
		}
	}

	return 0;
}