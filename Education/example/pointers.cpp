#include <iostream>

int main()
{
	int x = 0;
	int * ptr_x = &x;

	auto y = 0;
	auto ptr_y = &y;

	*ptr_x = 42;
	++(*ptr_y);

	int * ptr_z = nullptr;

	if (ptr_z)
	{
		std::cout << *ptr_z << '\n';
	}

	auto c = 0;

	const int * ptr_c = &c;
	int * const c_ptr = &c;

	const int * const c_ptr_c = &c;

	return 0;
}