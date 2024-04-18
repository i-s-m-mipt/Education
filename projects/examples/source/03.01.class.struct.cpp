#include <iostream>
#include <vector>

// =================================================================================================

struct S { int x{}, y{}, z{ 4 }; }; // good: capital letter for user-defined types

struct Point { double x = 0.0, y = 0.0; }; // good: do not forget initialization

// =================================================================================================

[[nodiscard]] inline Point make_point(double x, double y)
{
	if (x > 0.0 && y > 0.0)
	{
		return Point { x, y }; // note: temporary object
	}
	else return {}; // good: compact syntax, type deduction
}

// =================================================================================================

int main()
{
	S s1; // good: compact syntax, x = 0, y = 0, z = 4

	[[maybe_unused]] S s2 {         }; // note: x = 0, y = 0, z = 4, unnecessary {}
	[[maybe_unused]] S s3 { 1, 2, 3 }; // note: x = 1, y = 2, z = 3
	[[maybe_unused]] S s4 { 1, 2    }; // note: x = 1, y = 2, z = 4

	[[maybe_unused]] S s5 { .x { 1 }, .z { 3 } }; // note: x = 1, y = 0, z = 3
	[[maybe_unused]] S s6 { .x = 1,   .z = 3   }; // note: x = 1, y = 0, z = 3

//	S s7 { .y{ 2 }, .x{ 1 } }; // error: invalid initialization order

	s1.x = 42;

	const auto ptr = &s1;

//	(*ptr).y = 42; // bad: redundant syntax

	ptr->y = 42;

	auto & ref = s1.z;

	ref = 42;

	std::cout <<  s1.x << std::endl;
	std::cout <<  s1.y << std::endl;
	std::cout <<  s1.z << std::endl;

	std::cout << &s1   << std::endl;
	std::cout << &s1.x << std::endl; // note: same address as previous

	s1 = { 10, 20, 30 };

	s1 = { .x = 100, .z = 300 };

	[[maybe_unused]] const S s8 { 1, 2, 3 };

//	s8.x = 42; // error: constant object

	std::vector < Point > points = { {1.0, 2.0}, {3.0, 4.0} };

	return 0;
}