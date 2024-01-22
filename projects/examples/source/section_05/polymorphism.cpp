#include <iostream>

class Computer
{
public:

	virtual ~Computer() = default; // note: polymorphic base class

	virtual void run() const = 0;

}; // class Computer

struct Mobile_v1 : public Computer { void run() const override { std::cout << "Mobile_v1\n"; } };
struct Tablet_v1 : public Computer { void run() const override { std::cout << "Tablet_v1\n"; } };
struct Laptop_v1 : public Computer { void run() const override { std::cout << "Laptop_v1\n"; } };

void handle_v1(const Computer & computer) 
{
	computer.run(); // note: slower in runtime, but clear hierarchy
}

struct Mobile_v2 { void run() const { std::cout << "Mobile_v2\n"; } };
struct Tablet_v2 { void run() const { std::cout << "Tablet_v2\n"; } };
struct Laptop_v2 { void run() const { std::cout << "Laptop_v2\n"; } };

template < typename T > void handle_v2(const T & t)
{
	t.run(); // note: faster in runtime, but independent classes
}

int main()
{
	handle_v1(Mobile_v1());
	handle_v2(Mobile_v2());

	return 0;
}