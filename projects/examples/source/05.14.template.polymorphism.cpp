#include <iostream>

//  ================================================================================================

class Computer
{
public:

	virtual ~Computer() = default; 

	virtual void run() const = 0;

}; // class Computer

//  ================================================================================================

class Mobile_v1 : public Computer { public: void run() const override; };
class Tablet_v1 : public Computer { public: void run() const override; };
class Laptop_v1 : public Computer { public: void run() const override; };

//  ================================================================================================

void Mobile_v1::run() const { std::cout << "Mobile_v1" << std::endl; }
void Tablet_v1::run() const { std::cout << "Tablet_v1" << std::endl; }
void Laptop_v1::run() const { std::cout << "Laptop_v1" << std::endl; }

//  ================================================================================================

inline void handle_v1(const Computer & computer)
{
	computer.run(); 
}

//  ================================================================================================

class Mobile_v2 { public: void run() const { std::cout << "Mobile_v2" << std::endl; } };
class Tablet_v2 { public: void run() const { std::cout << "Tablet_v2" << std::endl; } };
class Laptop_v2 { public: void run() const { std::cout << "Laptop_v2" << std::endl; } };

//  ================================================================================================

template < typename T > inline void handle_v2(const T & computer)
{
	computer.run();
}

//  ================================================================================================

int main()
{
	handle_v1(Mobile_v1());
	handle_v2(Mobile_v2());

	return 0;
}