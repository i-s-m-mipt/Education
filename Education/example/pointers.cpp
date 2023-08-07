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
		std::cout << *ptr_z << std::endl;
	}

	auto c = 0;

	const int* ptr_c_1 = &c;
	int* const ptrc_c_2 = &c;

	return 0;
}