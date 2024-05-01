#include <iostream>

//  ================================================================================================

class Computer
{
public:

	virtual ~Computer() = default; // note: polymorphic base class

	virtual void run() const = 0;

}; // class Computer

//  ================================================================================================

class Mobile_v1 : public Computer { public: void run() const override { std::cout << "Mobile_v1" << std::endl; } };
class Tablet_v1 : public Computer { public: void run() const override { std::cout << "Tablet_v1" << std::endl; } };
class Laptop_v1 : public Computer { public: void run() const override { std::cout << "Laptop_v1" << std::endl; } };

//  ================================================================================================

inline void handle_v1(const Computer & computer) // note: slower in runtime, but clear hierarchy
{
	computer.run(); 
}

//  ================================================================================================

class Mobile_v2 { public: void run() const { std::cout << "Mobile_v2" << std::endl; } };
class Tablet_v2 { public: void run() const { std::cout << "Tablet_v2" << std::endl; } };
class Laptop_v2 { public: void run() const { std::cout << "Laptop_v2" << std::endl; } };

//  ================================================================================================

template < typename T > inline void handle_v2(const T & computer) // note: consider constraints
{
	computer.run(); // note: faster in runtime
}

//  ================================================================================================

int main()
{
	handle_v1(Mobile_v1());
	handle_v2(Mobile_v2());

	return 0;
}