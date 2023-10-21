import std;

void * allocate(std::size_t n)
{
	return operator new(n);
}

int main()
{
	auto x = 0;
	auto ptr_x = &x;

	void * ptr = ptr_x;

//	*ptr = 42; // error: invalid dereference

//	++ptr; // error: invalid pointer arithmetic

//	int * ptr_int = ptr; // error: invalid initialization

	auto ptr_object = static_cast < int * > (ptr);

	const std::size_t n = 10;

	auto ptr_ints = static_cast < int * > (allocate(n * sizeof(int)));

	return 0;
}