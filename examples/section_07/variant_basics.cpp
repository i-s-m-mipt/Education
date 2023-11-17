#include <cmath>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

struct S { explicit S([[maybe_unused]] int x) {} };

class A
{
public:

	~A() { std::cout << "destructor" << std::endl; }

}; // class A

class B {};

std::variant < std::monostate, int, double > handle(int x)
{
	if (x < 0)
	{
		return std::monostate();
	}
	else if (x == 0)
	{
		return x;
	}
	else
	{
		return std::sqrt(x);
	}
}

int main()
{
	[[maybe_unused]] std::variant < char, int, double > v1;

	v1 = 42; // note: now holding integer value

	std::get < int > (v1) += 42;

	if (auto ptr = std::get_if < int > (&v1); ptr)
	{
		*ptr = 42;
	}

//	std::variant < S, int > v2; // error: not default constructible

	[[maybe_unused]] std::variant < std::monostate, S, int > v3;

	std::variant < char, int, double > v4(3.14); // note: double

	std::cout << std::get < double > (v4) << std::endl;

//	std::variant < char, double > v5(42); // error: ambiguous selection

	[[maybe_unused]] std::variant < char, double > v6(std::in_place_type < double > , 42);
	[[maybe_unused]] std::variant < char, double > v7(std::in_place_index < 1 > ,     42);

	std::variant < int, int > v8(std::in_place_index < 0 >, 42);

	std::cout << v8.index() << std::endl;

	std::variant < A, B > v9;

	v9 = B(); // good: no memory leaks, destructor called

	if (auto result = handle(42); std::holds_alternative < double > (result))
	{
		std::cout << std::get < double > (result) << std::endl;
	}

	return 0;
}