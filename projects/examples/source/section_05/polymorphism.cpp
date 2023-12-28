#include <iostream>

class Shape
{
public:

	virtual ~Shape() = default;

	virtual void draw() const = 0;

}; // class Shape

class Triangle_v1 : public Shape
{
public:

	void draw() const override { std::cout << "Triangle_v1" << std::endl; }

}; // class Triangle_v1 : public Shape

void handle_v1(const Shape & shape) 
{
	shape.draw(); // note: slower in runtime, but clear hierarchy
}

class Triangle_v2
{
public:

	void draw() const { std::cout << "Triangle_v2" << std::endl; }

}; // class Triangle_v2

template < typename T > void handle_v2(const T & t)
{
	t.draw(); // note: faster in runtime, but independent classes
}

int main()
{
	handle_v1(Triangle_v1());
	handle_v2(Triangle_v2());

	return 0;
}