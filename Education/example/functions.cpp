#include <iostream>

[[nodiscard]] int f(int x);

[[nodiscard]] int g(int x, int y, int z = 1)
{
	return (x + y + z);
}

void test_pointers(int * x, const int * y)
{
	if (!x || !y)
	{
		return;
	}

	std::cout << *x << ' ' << *y << '\n';

	++(*x);
//	++(*y); // error

	std::cout << *x << ' ' << *y << '\n';
}

void test_references(int & x, const int & y)
{
	std::cout << x << ' ' << y << '\n';

	++x;
//	++y; // error

	std::cout << x << ' ' << y << '\n';
}

[[maybe_unused]] void set_code(int * code = nullptr)
{
	[[maybe_unused]] auto local_code = (code ? *code : 1234);
}

void test_array(int * a, int size)
{
	for (auto i = 0; i < size; ++i)
	{
		std::cout << a[i];

		std::cout << (i + 1 == size ? '\n' : ' ');
	}
}

int * get_dangling_ptr()
{
	/*static const*/ int d = 42;

	return &d; // warning
}

int & get_dangling_ref()
{
	/*static const*/ int d = 42;

	return d; // warning
}

void h()
{
	auto x = 0;

	static auto y = 0;

	std::cout << x++ << ' ' << y++ << '\n';

	return;
}

void print(bool x)
{
	std::cout << x << '\n';
}

void print(double x)
{
	std::cout << x << '\n';
}

int factorial(int n)
{
	return (n < 2 ? 1 : n * factorial(n - 1));
}

inline auto max(int x, int y)
{
	return (x > y ? x : y);
}

int main()
{
	[[maybe_unused]] auto result = g(f(4), f(7));

	auto x = 0;
	auto y = 0;

	test_pointers(&x, &y);

	std::cout << x << ' ' << y << '\n';

	test_references(x, y);

	std::cout << x << ' ' << y << '\n';

	int array_1[]{ 1, 2, 3, 4, 5 };

	test_array(array_1, sizeof(array_1) / sizeof(int));

	const auto size = 5;

	auto array_2 = new int[size]{ 1, 2, 3, 4, 5 };

	test_array(array_2, size);

	delete[] array_2;

	auto bad_ptr = get_dangling_ptr();
	auto bad_ref = get_dangling_ref();

	std::cout << *bad_ptr << ' ' << bad_ref << '\n';

	h(); 
	h(); 
	h();

	std::cout << *bad_ptr << ' ' << bad_ref << '\n';

	print(true);
	print(3.14);
//	print(1234); // error

	std::cout << factorial(5) << '\n';

	std::cout << max(4, 7) << '\n';

	return 0;
}

int f(int x)
{
	return (x + 1);
}