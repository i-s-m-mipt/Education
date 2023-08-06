#include <iostream>

void * allocate(std::size_t n)
{
	// ...
}

int main()
{
	auto x = 0;
	auto ptr_x = &x;

	void * ptr = ptr_x;

	auto ptr_object = static_cast < int * > (ptr);

	const std::size_t n = 10;

	auto ptr_ints = static_cast < int * > (allocate(n * sizeof(int)));

	return 0;
}