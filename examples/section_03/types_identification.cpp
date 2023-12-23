#include <iostream>

class Shape // note: polymorphic base class with virtual destructor
{
public:

	virtual ~Shape() = default;

}; // class Shape 

class Polygon : public Shape {};
class Ellipse : public Shape {};

int main()
{
	Shape * s_ptr = new Polygon;

	[[maybe_unused]] auto p1_ptr = dynamic_cast < Polygon * > (s_ptr); // note: runtime downcasting

	delete s_ptr;

	s_ptr = new Ellipse;

	auto p2_ptr = dynamic_cast < Polygon * > (s_ptr); // note: use virtual functions instead of downcasting

	if (!p2_ptr)
	{
		std::cout << "invalid dynamic cast" << std::endl;
	}

	delete s_ptr;

	return 0;
}