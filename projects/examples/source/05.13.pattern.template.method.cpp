#include <iostream>

//  ================================================================================================

class Computer
{
public:

	virtual ~Computer() = default; 

	void run() const { f1(); f2(); f3(); f4(); f5(); std::cout << std::endl; } 

private:

	void f1() const { std::cout << "1 "; }
	void f3() const { std::cout << "3 "; }
	void f5() const { std::cout << "5 "; }

private:

	virtual void f2() const = 0;
	virtual void f4() const = 0;

}; // class Computer

//  ================================================================================================

class Mobile : public Computer
{
private:

	void f2() const override { std::cout << "M "; }
	void f4() const override { std::cout << "M "; }

}; // class Mobile : public Computer

//  ================================================================================================

class Tablet : public Computer
{
private:

	void f2() const override { std::cout << "T "; }
	void f4() const override { std::cout << "T "; }

}; // class Tablet : public Computer

//  ================================================================================================

class Laptop : public Computer
{
private:

	void f2() const override { std::cout << "L "; }
	void f4() const override { std::cout << "L "; }

}; // class Laptop : public Computer

//  ================================================================================================

int main()
{
	const Computer * const mobile = new const Mobile();

	mobile->run(); 
	
	delete mobile;

	return 0;
}