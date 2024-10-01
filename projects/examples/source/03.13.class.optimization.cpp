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

	std::cout << "sizeof(E) = " << sizeof(E) << std::endl;

	std::cout << "sizeof(X) = " << sizeof(X) << std::endl;
	std::cout << "sizeof(Y) = " << sizeof(Y) << std::endl;
	std::cout << "sizeof(Z) = " << sizeof(Z) << std::endl;

//  ================================================================================================

	std::cout << "sizeof(A) = " << sizeof(A) << std::endl;
	std::cout << "sizeof(B) = " << sizeof(B) << std::endl;
	std::cout << "sizeof(C) = " << sizeof(C) << std::endl;

	return 0;
}