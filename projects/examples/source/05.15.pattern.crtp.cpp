#include <iostream>

//  ================================================================================================

template < class D > class Computer
{
public:

	virtual ~Computer() = default;

	void run() const
	{
		static_cast < const D * > (this)->run_implementation();
	}

	void run_implementation() const { std::cout << "Computer" << std::endl; }

}; // template < class D > class Computer

//  ================================================================================================

template < typename D > inline void destroy(const Computer < D > * computer)
{
	delete static_cast < const D * > (computer);
}

//  ================================================================================================

class Tablet : public Computer < Tablet > {};

//  ================================================================================================

class Laptop : public Computer < Laptop >
{
public: void run_implementation() const { std::cout << "Laptop" << std::endl; }
}; 

//  ================================================================================================

template < typename T > inline void handle(const T & computer)
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