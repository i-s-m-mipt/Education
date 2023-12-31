#include <iostream>
#include <vector>

class Shape
{
public:

	Shape()
	{
//		print(); // bad: base version
	}

	virtual ~Shape()
	{
//		print(); // bad: base version
	}

public:

	virtual void print() const // note: can be redefined in derived classes
	{
		std::cout << "Shape" << std::endl;
	}

}; // class Shape

class Polygon final : public Shape // note: final class in hierarchy
{
public:

	void print() const override final // note: final function in hierarchy
	{
		std::cout << "Polygon" << std::endl;
	}

}; // class Polygon final : public Shape

/*
class Rectangle : public Polygon // error: class Polygon declared final
{
public:

	void print() const override // error: print declared final in class Polygon
	{
		std::cout << "Rectangle" << std::endl;
	}

}; // class Rectangle : public Polygon
*/

class Ellipse : public Shape // note: not final class in hierarchy
{
public:

	void print() const override // note: not final function in hierarchy
	{
		std::cout << "Ellipse" << std::endl;
	}

}; // class Ellipse : public Shape

class Abstract_Base // note: interface class like in Java
{
public:

	virtual ~Abstract_Base() {};

public:

	virtual void print() const = 0; // note: must be redefined in derived classes

}; // class Abstract_Base

void Abstract_Base::print() const // note: definition must be provided separately
{
	std::cout << "default implementation" << std::endl;
}

class Derived : public Abstract_Base
{
public:

	void print() const override
	{
		std::cout << "derived implementation" << std::endl;

		Abstract_Base::print(); // note: possible default implementation
	}

}; // class Derived : public Abstract_Base

int main()
{
	Polygon p;

	Shape * s_ptr = &p; // note: works with pointers and references

//	Shape s = p; // bad: object slicing

	s_ptr->print();

	Polygon p1;
	Polygon p2;
	Ellipse e1;
	Ellipse e2;

	std::vector < Shape * > shapes = { &p1, &p2, &e1, &e2 };

	for (std::size_t i = 0; i < shapes.size(); ++i)
	{
		shapes[i]->print();
	}

	s_ptr = new Polygon;

	s_ptr->print();

	delete s_ptr; // note: important virtual destructor

	Derived d;

	Abstract_Base * ab_ptr = &d; // good: interface class

	ab_ptr->print();

//	Abstract_Base ab; // error: abstract base class

	return 0;
}