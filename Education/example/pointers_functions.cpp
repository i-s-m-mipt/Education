#include <iostream>

void print(int x)
{
	std::cout << x << std::endl;
}

void apply(void (*f)(int), int argument)
{
	f(argument);
}

int main()
{
	void (*print_ptr)(int) = &print;

	(*print_ptr)(42);

	apply(print, 42);

	return 0;
}