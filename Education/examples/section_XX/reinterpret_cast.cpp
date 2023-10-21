import std;

template < typename T >
auto distance_in_bytes(T * first, T * last)
{
	return (reinterpret_cast < char * > (last) - reinterpret_cast < char * > (first));
}

int main()
{
	auto ptr_int = new int(42);

	std::cout << *ptr_int << std::endl;

	auto ptr_char = reinterpret_cast < char * > (ptr_int);

	std::cout << *ptr_char << std::endl;

	auto ptr_double = new double(1234.5678);

	std::cout.write(reinterpret_cast < const char * > (ptr_double), sizeof(double));

	std::cout << std::endl;

	const std::size_t size = 10;

	int a[size]{};

	std::cout << &a[size - 1] - &a[0] << std::endl; // note: pointer arithmetic

	std::cout << distance_in_bytes(&a[0], &a[size - 1]) << std::endl;

	return 0;
}