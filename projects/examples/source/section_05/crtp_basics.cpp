#include <iostream>

template < class Derived > class Computer
{
public:

	virtual ~Computer() = default; // note: polymorphic base class

	void run() const // note: non-virtual function due to template
	{
		static_cast < const Derived * > (this)->run_implementation();
	}

}; // template < class Derived > class Computer

class Laptop : public Computer < Laptop >
{
public:

	void run_implementation() const { std::cout << "Laptop" << std::endl; }

}; // class Laptop : public Computer < Laptop >

template < typename T > void handle(const T & t) { t.run(); }

int main()
{
	handle(Laptop());

	return 0;
}