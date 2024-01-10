#include <iostream>
#include <numeric>

int * search(int * a, std::size_t l, std::size_t r, int k)
{
	if (r == 0) // good: extreme case
	{
		return nullptr;
	}

	if (r == 1) // good: extreme case
	{
		return (a[0] == k ? a : nullptr);
	}

	while (l < r) // good: one comparison in loop condition
	{
		auto middle = std::midpoint(l, r); // good: optimized for possible overflows

		if (a[middle] < k) // good: one comparison in selection condition with two branches
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
	const std::size_t size = 7;

	auto a = new int[size]{1, 3, 4, 5, 6, 7, 8 }; // note: consider std::vector with iterators

	for (auto i = a[0] - 1; i <= a[size - 1] + 1; ++i)
	{
		std::cout << "index of " << i << " in array: ";

		if (auto ptr = search(a, 0, size - 1, i); ptr) // note: not half-open interval
		{
			std::cout << ptr - a << std::endl; // note: get index through pointer arithmetic
		}
		else
		{
			std::cout << "not found" << std::endl;
		}
	}

	delete[] a; // good: no memory leak

	return 0;
}