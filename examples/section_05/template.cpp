#include <iostream>

class Base
{
public:

	void run() const // note: template method
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

}; // class Base

class Derived_1 : public Base
{
	void b() const override { std::cout << "b "; }
	void d() const override { std::cout << "d "; }

}; // class Derived_1 : public Base

class Derived_2 : public Base
{
	void b() const override { std::cout << "B "; }
	void d() const override { std::cout << "D "; }

}; // class Derived_2 : public Base

int main()
{
	Base * b1 = new Derived_1;
	Base * b2 = new Derived_2;

	b1->run();
	b2->run();

	delete b1; // good: no memory leak
	delete b2; // good: no memory leak

	return 0;
}