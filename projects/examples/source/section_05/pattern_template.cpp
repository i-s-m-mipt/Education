#include <iostream>

class Computer
{
public:

	virtual ~Computer() = default; // note: polymorphic base class

	void run() const // note: template method, not template < ... >
	{ 
		a(); b(); c(); d(); e(); std::cout << std::endl;
	} 

private:

	void a() const { std::cout << "a "; }
	void c() const { std::cout << "c "; }
	void e() const { std::cout << "e "; }

private: // note: non-virtual interface

	virtual void b() const = 0;
	virtual void d() const = 0;

}; // class Computer

class Mobile : public Computer
{
public:

	void b() const override { std::cout << "M "; }
	void d() const override { std::cout << "M "; }

}; // class Mobile : public Computer

class Tablet : public Computer
{
public:

	void b() const override { std::cout << "T "; }
	void d() const override { std::cout << "T "; }

}; // class Tablet : public Computer

class Laptop : public Computer
{
public:

	void b() const override { std::cout << "L "; }
	void d() const override { std::cout << "L "; }

}; // class Laptop : public Computer

int main()
{
	const Computer * const mobile = new Mobile;

	mobile->run(); 
	
	delete mobile; // good: no memory leak

	return 0;
}