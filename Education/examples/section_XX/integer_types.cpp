import std;

int factorial(int n)
{
	return (n < 2 ? 1 : n * factorial(n - 1));
}

unsigned long long operator""_km(unsigned long long distance)
{
	return distance;
}

int main()
{
	short s = 0; // note: used in systems with limited memory

	std::cout << sizeof(s) << std::endl; // note: at least 16 bits

	int i = 0; // note: used in most common cases

	std::cout << sizeof(i) << std::endl; // note: at least 16 bits, usually 32 bits

	long l = 0;

	std::cout << sizeof(l) << std::endl; // note: at least 32 bits

	long long ll = 0; // note: used as the largest integer type

	std::cout << sizeof(ll) << std::endl; // note: at least 64 bits

//	signed int si = 0; // bad: redundant syntax, enabled by default
	  
	[[maybe_unused]] unsigned int ui = 0; // note: unsigned representation
	
	/*
	for (unsigned int j = 100; j >= 0; --j) // warning: infinite loop
	{
		std::cout << j << std::endl;
	}
	*/

	const std::size_t size = 10; // good: type alias for sizes

	auto x = 0; // note: auto -> int

	auto y = 0ull; // note: auto -> unsigned long long, looks like Hungarian notation

//	for (auto j = 0; j < size; ++j) {} // bad: imcompatible types

//	for (auto j = 0ull; j < size; ++j) {} // bad: unpleasant suffix

	for (std::size_t j = 0; j < size; ++j) {}

	auto z = 100_km; // note: user-defined literal for better readability

//	std::cout << factorial(20) << std::endl; // bad: overflow problem

	return 0;
}