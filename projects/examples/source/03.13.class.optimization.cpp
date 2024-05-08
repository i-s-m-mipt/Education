#include <iostream>

//  ================================================================================================

class Container
{
public:

	Container(                  ) { std::cout << "Container::Container (main)" << std::endl; }
	Container(const Container & ) { std::cout << "Container::Container (copy)" << std::endl; }
	Container(      Container &&) { std::cout << "Container::Container (move)" << std::endl; }

	Container & operator=(const Container &) 
	{ 
		std::cout << "Container::operator= (copy)" << std::endl; return *this; 
	}

	Container & operator=(Container &&) 
	{ 
		std::cout << "Container::operator= (move)" << std::endl; return *this; 
	}

   ~Container() { std::cout << "Container::~Container" << std::endl; }

}; // class Container

//  ================================================================================================

[[nodiscard]] inline Container f() {                                     return Container(); }
[[nodiscard]] inline Container g() { const auto container = Container(); return container  ; }

//  ================================================================================================

class E {};

class X { const char c{};                       const E e;      };
class Y { const char c{}; [[no_unique_address]] const E e;      };
class Z { const char c{}; [[no_unique_address]] const E e1, e2; };

//  ================================================================================================

class A {}; // support: класс boost::compressed_pair

class B : public A {};
class C : public B {};

//  ================================================================================================

int main()
{
	[[maybe_unused]] const auto container_1 = f();
	[[maybe_unused]] const auto container_2 = g();

//  ================================================================================================

	std::cout << "size of E: " << sizeof(E) << std::endl; // output: >= 1

	std::cout << "size of X: " << sizeof(X) << std::endl; // output: >= 2
	std::cout << "size of Y: " << sizeof(Y) << std::endl; // output: == 1
	std::cout << "size of Z: " << sizeof(Z) << std::endl; // output: >= 2

//  ================================================================================================

	std::cout << "size of A: " << sizeof(A) << std::endl; // output: == 1
	std::cout << "size of B: " << sizeof(B) << std::endl; // output: == 1
	std::cout << "size of C: " << sizeof(C) << std::endl; // output: == 1

	return 0;
}