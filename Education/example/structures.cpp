#include <iostream>

struct Object // good: capital letter for user-defined types
{
	int a{};
	int b{};
	int c{ 4 };
}; // note: semicolon is necessary

struct Point
{
	double x = 0.0;
	double y = 0.0;
};

struct Big_Object
{
	double a[100]{}; // note: big data
};

[[maybe_unused]] void f(const Big_Object & big_object) // good: pass big data by constant reference
{
	std::cout << big_object.a[0] << '\n';
}

[[maybe_unused]] Point make_point(double x, double y)
{
	if (x > 0.0 && y > 0.0)
	{
		return Point{ x, y }; // note: temporary object
	}
	else
	{
		return {}; // good: compact syntax, type deduction
	}
}

struct Node; // note: forward declaration, cyclic dependence

struct Link
{
	Node * left;  // note: declaration is enough
	Node * right; // note: declaration is enough
};

struct Node
{
	Link links[2]; // note: definition required
};

int main()
{
	Object object_1; // good: compact syntax, a = 0, b = 0, c = 4

	[[maybe_unused]] Object object_2{};          // note: a = 0, b = 0, c = 4, unnecessary {}
	[[maybe_unused]] Object object_3{ 1, 2, 3 }; // note: a = 1, b = 2, c = 3
	[[maybe_unused]] Object object_4{ 1, 2 };    // note: a = 1, b = 2, c = 4

	[[maybe_unused]] Object object_5{ .a{ 1 }, .c{ 3 } }; // note: a = 1, b = 0, c = 3
	[[maybe_unused]] Object object_6{ .a = 1, .c = 3 };   // note: a = 1, b = 0, c = 3

//	Object object_7{ .b{ 2 }, .a{ 1 } }; // error: invalid initialization order

	Point points[] =
	{
		{1.0, 1.0},
		{2.0, 2.0},
		{3.0, 3.0}
	};

	object_1.a = 42;

	std::cout << object_1.a << '\n';

	auto ptr = &object_1;

//	(*ptr).b = 42; // bad: redundant syntax

	ptr->b = 42;

	std::cout << object_1.b << '\n';

	auto & ref = object_1.c;

	ref = 42;

	std::cout << object_1.c << '\n';

	object_1 = { 10, 20, 30 };

	object_1 = { .a = 100, .c = 300 };

	[[maybe_unused]] const Object object_8{ 1, 2, 3 };

//	object_8.a = 42; // error: constant object

	return 0;
}