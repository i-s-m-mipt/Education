#include <iostream>

int main()
{
	const std::size_t size = 10;

	auto ptr_int       = new int(42);
	auto ptr_int_array = new int[size]{};

	++(*ptr_int);

	ptr_int_array[5] = 42;

	std::cout << *ptr_int << std::endl;

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << ptr_int_array[i] << ' ';
	}

	delete   ptr_int;
	delete[] ptr_int_array;

	if (auto ptr_char = new(std::nothrow) char[size] {}; ptr_char)
	{
		ptr_char[0] = 'a';

		// ...

		delete[] ptr_char;
	}

	return 0;
}