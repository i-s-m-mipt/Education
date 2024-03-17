#include <iostream>

[[nodiscard]] auto f() { std::cout << "Hello, world!" << std::endl; return 0; }

auto x = f(); // note: global variable

class C
{
public:

	 C() { std::cout << "Hello, world!" << std::endl; }
	~C() { std::cout << "Hello, world!" << std::endl; }

}; // class C

C c; // note: global variable

#define return std::cout << "Hello, world!" << std::endl;

int main() 
{
//	return 0; // note: main has only return 0; statement
}