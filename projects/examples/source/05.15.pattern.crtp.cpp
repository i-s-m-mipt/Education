#include <iostream>

// =================================================================================================

template < class D > class Computer
{
public:

	virtual ~Computer() = default; // note: option 1 is hybrid-time polymorphism

	void run() const // note: non-virtual function due to template
	{
		static_cast < const D * > (this)->run_implementation(); // note: possible infinite recursion
	}

}; // template < class D > class Computer

// =================================================================================================

template < typename D > inline void destroy(const Computer < D > * computer)
{
	delete static_cast < const D * > (computer); // note: option 2 is compile-time polymorphism
}

// =================================================================================================

class Laptop : public Computer < Laptop >
{
public:
	
	void run_implementation() const { std::cout << "Laptop" << std::endl; }

}; // class Laptop : public Computer < Laptop >

// =================================================================================================

template < typename T > inline void handle(const T & computer) // note: consider constraints
{ 
	computer.run(); 
}

// =================================================================================================

int main()
{
	handle(Laptop());

	return 0;
}