#include <iostream>

class Shape
{
public:

	virtual ~Shape() = default;

	virtual void draw() const = 0;

}; // class Shape

class Triangle : public Shape
{
public:

	void draw() const override { std::cout << "Triangle" << std::endl; }

}; // class Triangle

class Rectangle : public Shape
{
public:

	void draw() const override { std::cout << "Rectangle" << std::endl; }

}; // class Rectangle

void handle(const Shape & shape)
{
	shape.draw();
}

int main()
{
	handle(Triangle());

	return 0;
}