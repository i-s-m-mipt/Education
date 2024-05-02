#include <iostream>

//  ================================================================================================

[[nodiscard]] inline int    get_prvalue() { return 42; }
/*
[[nodiscard]] inline int && get__xvalue() { return 42; } // warning: dangling reference
*/
[[nodiscard]] inline int &  get__lvalue() { static int x = 42; return x; }

//  ================================================================================================

int main()
{
	[[maybe_unused]] double d = 3.14;

	const int i = 42;

//  ================================================================================================

//	int &  lvalue_1 = get_prvalue(); // error: lvalue reference cannot be bound to prvalue

	[[maybe_unused]] int &  lvalue_2 = get__lvalue();

//	int &  lvalue_3 = d; // error: lvalue reference cannot be bound to prvalue
//	int &  lvalue_4 = i; // error: lvalue reference cannot be bound to constant lvalue

//  ================================================================================================

	[[maybe_unused]] int && rvalue_1 = get_prvalue();

//	int && rvalue_2 = get__lvalue(); // error: rvalue reference cannot be bound to lvalue

//	int && rvalue_3 = d; // warning: dangerous double to int conversion

//	int && rvalue_4 = i; // error: rvalue reference cannot be bound to lvalue

//  ================================================================================================
	
	[[maybe_unused]] const int &  const_lvalue_1 = get_prvalue();
	[[maybe_unused]] const int &  const_lvalue_2 = get__lvalue();

//	const int &  const_lvalue_3 = d; // warning: dangerous double to int conversion

	[[maybe_unused]] const int &  const_lvalue_4 = i;

//  ================================================================================================
	
	[[maybe_unused]] const int && const_rvalue_1 = get_prvalue();

//	const int && const_rvalue_2 = get__lvalue(); // error: constant rvalue reference cannot be bound to lvalue

//	const int && const_rvalue_3 = d; // warning: dangerous double to int conversion

//	const int && const_rvalue_4 = i; // error: constant rvalue reference cannot be bound to lvalue

	return 0;
}