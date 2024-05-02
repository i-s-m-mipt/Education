#include <iostream>

//  ================================================================================================

template < class D > class Computer
{
public:

	virtual ~Computer() = default; // note: option 1 is hybrid-time polymorphism

	void run() const // note: non-virtual function due to template
	{
		static_cast < const D * > (this)->run_implementation(); // note: possible infinite recursion
	}

	void run_implementation() const { std::cout << "Computer" << std::endl; } // note: default

}; // template < class D > class Computer

//  ================================================================================================

template < typename D > inline void destroy(const Computer < D > * computer)
{
	delete static_cast < const D * > (computer); // note: option 2 is compile-time polymorphism
}

//  ================================================================================================

class Tablet : public Computer < Tablet > {};

//  ================================================================================================

class Laptop : public Computer < Laptop >
{
public: void run_implementation() const { std::cout << "Laptop" << std::endl; }
}; 

//  ================================================================================================

template < typename T > inline void handle(const T & computer) // note: consider constraints
{ 
	computer.run(); 
}

//  ================================================================================================

int main()
{
	handle(Tablet());
	handle(Laptop());

	return 0;
}