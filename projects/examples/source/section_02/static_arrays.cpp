#include <iostream>
#include <utility>

int main()
{
	const std::size_t size = 10; // note: compile-time constant variable

	int a[size]{}; // good: zero initialized array

	[[maybe_unused]] int b[size]{ 1, 2, 3 }; // note: elements: { 1, 2, 3, 0, 0, 0, 0, 0, 0, 0 }

	[[maybe_unused]] int c[]{ 1, 2, 3 }; // note: elements: { 1, 2, 3 }, size deduction -> 3

//	int d[2]{ 1, 2, 3 }; // error: too many initializers

//	int e[1'000'000'000]{}; // bad: array is too large, use dynamic array

	std::cout << sizeof(a) / sizeof(a[0]) << std::endl; // note: old-style computation

	std::cout << std::size(a) << std::endl; // good: common for static arrays and containers

	*a = 42; // note: array name is a pointer to the first element

	const auto m = size / 2;

	*(a + m) = 42; // note: pointer arithmetic

//	*(a + 100) = 42; // bad: undefined behavior

	std::cout << a[m] << std::endl; // good: standard index access operator syntax

//	std::cout << *(&a[0] + m) << std::endl; // bad: redundant syntax

	std::cout << *(a + m) << std::endl;
	std::cout << *(m + a) << std::endl;

//	std::cout << m[a] << std::endl; // bad: inconvenient index access operator syntax

	std::cout << (a + m + 1) - (a + m - 1) << std::endl; // note: distance between elements

//	auto delta = b - a; // bad: pointers to different arrays

	for (int * p = a; p != (a + size); ++p)
	{
		std::cout << *p;

		std::cout << (p + 1 == a + size ? '\n' : ' '); // good: compact formatting
	}

	std::cout << "Enter array size <= 1024: "; std::size_t n{}; std::cin >> n;

	std::cout << "Enter " << n << " integer values: ";

	const std::size_t buffer_size = 1024; // note: constant size with margin

	int s[buffer_size]{};

	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> s[i];
	}

	for (std::size_t i = 0; i < n - 1; ++i) // note: bubble sort
	{
		for (std::size_t j = i + 1; j < n; ++j)
		{
			if (s[i] > s[j])
			{
				std::swap(s[i], s[j]);
			}
		}
	}

	for (std::size_t i = 0; i < n; ++i)
	{
		std::cout << s[i] << (i + 1 == n ? '\n' : ' ');
	}

	return 0;
}