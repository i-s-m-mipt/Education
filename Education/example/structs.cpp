#include <iostream>
#include <string>
#include <vector>

struct Person
{
	std::string name = "default";
	std::size_t age  = 0;
};

struct Node;

struct Link
{
	Node * left;
	Node * right;

	// ...
};

struct Node
{
	std::vector < Link > links;

	// ...
};

struct Point
{
	double x = 0.0;
	double y = 0.0;
};

int main()
{
	Person p_1;
	Person p_2{ "Matthias", 27 };

	p_1.name = "Matthias";

	auto ptr = &p_1;

	ptr->age = 28;

	std::vector < Point > points =
	{
		{1.0, 1.0},
		{2.0, 2.0},
		{3.0, 3.0}
	};

	return 0;
}