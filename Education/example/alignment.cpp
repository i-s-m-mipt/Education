#include <cassert>
#include <iomanip>
#include <iostream>
#include <type_traits>

struct S1
{
	char  c;
	int   i;
	short s;
};

struct S2
{
	char  c;
	short s;
	int   i;
};

struct alignas(alignof(double)) S3
{
	char  c;
	int   i;
	short s;
};

int main()
{
	std::cout << alignof(char) << ' ' << sizeof(char) << std::endl;
	std::cout << alignof(int*) << ' ' << sizeof(int*) << std::endl;

	std::cout << alignof(S1) << ' ' << sizeof(S1) << std::endl;
	std::cout << alignof(S2) << ' ' << sizeof(S2) << std::endl;
	std::cout << alignof(S3) << ' ' << sizeof(S3) << std::endl;

	static_assert(std::alignment_of_v < double > == 8, "invalid double alignment");

	alignas(16)   int a[10]{};
	alignas(1024) int b[10]{};

	std::cout << std::hex << a << std::endl;
	std::cout << std::hex << b << std::endl;

	return 0;
}