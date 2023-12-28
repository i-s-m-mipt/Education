#include <iostream>

template < class Derived > class Shape
{
public:

	virtual ~Shape() = default;

public:

	void draw() const
	{
		static_cast < const Derived * > (this)->draw_implementation();
	}

}; // template < class Derived > class Shape

class Triangle : public Shape < Triangle >
{
public:

	void draw_implementation() const
	{
		std::cout << "triangle" << std::endl;
	}

}; // class Triangle : public Shape < Triangle >

template < typename T > void handle(const T & t)
{
	t.draw();
}

int main()
{
	handle(Triangle());

	return 0;
}