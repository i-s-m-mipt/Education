#include <iostream>
#include <vector>

struct S { int a{}, b{}, c{ 4 }; }; // good: capital letter for user-defined types

struct Point { double x = 0.0, y = 0.0; }; // good: do not forget initialization

[[nodiscard]] inline Point make_point(double x, double y)
{
	if (x > 0.0 && y > 0.0)
	{
		return Point{ x, y }; // note: temporary object
	}
	else return {}; // good: compact syntax, type deduction
}

int main()
{
	S s1; // good: compact syntax, a = 0, b = 0, c = 4

	[[maybe_unused]] S s2{         }; // note: a = 0, b = 0, c = 4, unnecessary {}
	[[maybe_unused]] S s3{ 1, 2, 3 }; // note: a = 1, b = 2, c = 3
	[[maybe_unused]] S s4{ 1, 2    }; // note: a = 1, b = 2, c = 4

	[[maybe_unused]] S s5{ .a { 1 }, .c { 3 } }; // note: a = 1, b = 0, c = 3
	[[maybe_unused]] S s6{ .a = 1,   .c = 3   }; // note: a = 1, b = 0, c = 3

//	S s7{ .b{ 2 }, .a{ 1 } }; // error: invalid initialization order

	std::vector < Point > points = { {1.0, 2.0}, {3.0, 4.0} };

	s1.a = 42;

	std::cout << s1.a << std::endl;

	const auto ptr = &s1;

//	(*ptr).b = 42; // bad: redundant syntax

	ptr->b = 42;

	std::cout << s1.b << std::endl;

	auto & ref = s1.c;

	ref = 42;

	std::cout << s1.c << std::endl;

	std::cout << &s1 << std::endl;

	std::cout << &s1.a << std::endl; // note: same address as previous

	s1 = { 10, 20, 30 };

	s1 = { .a = 100, .c = 300 };

	[[maybe_unused]] const S s8{ 1, 2, 3 };

//	s8.a = 42; // error: constant object

	return 0;
}