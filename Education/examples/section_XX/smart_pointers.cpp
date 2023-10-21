#include <iostream>
#include <memory>

struct B;

struct A
{
	A() { std::cout << "A()" << std::endl; }
	~A() { std::cout << "~A()" << std::endl; }

	std::shared_ptr < B > b;
};


struct B
{
	B() { std::cout << "B()" << std::endl; }
	~B() { std::cout << "~B()" << std::endl; }

	std::shared_ptr < A > a; // weak_ptr
};

int main(int argc, char** argv)
{
	{
		auto a = std::make_shared < A >();

		a->b = std::make_shared < B >();
		a->b->a = a;
	}

	system("pause");

	return EXIT_SUCCESS;
}