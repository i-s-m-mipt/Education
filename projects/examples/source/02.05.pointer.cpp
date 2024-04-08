#include <iostream>

int main()
{
	int       x =  0;
	int * ptr_x = &x;

	auto      y =  0;
	auto  ptr_y = &y;

	     *ptr_x = 42;
	  ++(*ptr_y);

	std::cout << ptr_x << ' ' << *ptr_x << std::endl;
	std::cout << ptr_y << ' ' << *ptr_y << std::endl;

	int * ptr_z = nullptr; // good: nullptr instead of 0

	[[maybe_unused]] auto n = nullptr; // note: auto -> std::nullptr_t

//	*ptr_z = 42; // error: dereferencing nullptr

	if (ptr_z) // good: check pointer before dereferencing
	{
		std::cout << *ptr_z << std::endl;
	}

	auto a = 0;

	[[maybe_unused]] const int * pc_1 = &a;

//	*pc = 42; // error: constant value

	[[maybe_unused]] int const * pc_2 = &a; // note: same as pc_1

	[[maybe_unused]] int * const cp = &a;

//	cp = nullptr; // error: constant pointer

	[[maybe_unused]] const int * const cpc = &a;

	const auto b = 0;

//	int * p = &b; // error: pointer to non-constant value

	[[maybe_unused]] const int * pc = &b;

	return 0;
}