#include <cassert>
#include <iomanip>
#include <iostream>
#include <type_traits>

struct S1
{
	char  c; // note: 1 byte(s)
	int   i; // note: 4 byte(s)
	short s; // note: 2 byte(s)

}; // struct S1

struct S2
{
	char  c; // note: 1 byte(s)
	short s; // note: 2 byte(s)
	int   i; // note: 4 byte(s)

}; // struct S2

struct alignas(alignof(double)) S3
{
	char  c; // note: 1 byte(s)
	short s; // note: 2 byte(s)
	int   i; // note: 4 byte(s)
	
}; // struct alignas(alignof(double)) S3

struct alignas(32) S4
{
	double data[4];

}; // struct alignas(32) S4

int main()
{
	std::cout << "char: " << alignof(char) << ' ' << sizeof(char) << std::endl;
	std::cout << "int*: " << alignof(int*) << ' ' << sizeof(int*) << std::endl;

	std::cout << "S1: " << alignof(S1) << ' ' << sizeof(S1) << std::endl;
	std::cout << "S2: " << alignof(S2) << ' ' << sizeof(S2) << std::endl;
	std::cout << "S3: " << alignof(S3) << ' ' << sizeof(S3) << std::endl;
	std::cout << "S4: " << alignof(S4) << ' ' << sizeof(S4) << std::endl;

	static_assert(std::alignment_of_v < double > == 8);

	alignas(16)   int a[10]{};
	alignas(1024) int b[10]{};

	std::cout << std::hex << a << std::endl;
	std::cout << std::hex << b << std::endl;

	return 0;
}