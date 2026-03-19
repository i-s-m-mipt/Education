////////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

////////////////////////////////////////////////////////

// section : Rvalue References

////////////////////////////////////////////////////////

// content : Copy and Move Semantics
//
// content : Function std::move

////////////////////////////////////////////////////////

#include <print>
#include <utility>

////////////////////////////////////////////////////////

struct Entity {};

////////////////////////////////////////////////////////

void test(Entity       & ) { std::print("test (1)\n"); }

void test(Entity const & ) { std::print("test (2)\n"); }

void test(Entity       &&) { std::print("test (3)\n"); }

void test(Entity const &&) { std::print("test (4)\n"); }

////////////////////////////////////////////////////////

int main()
{
	Entity       entity_1;

	Entity const entity_2;

//  ---------------------------------

	test(entity_1);

	test(entity_2);

//  ---------------------------------

	test(std::move(entity_1));

//	test(std::move(entity_2)); // bad

//  ---------------------------------

	test(Entity());
}

////////////////////////////////////////////////////////