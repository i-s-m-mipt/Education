#include <iostream>

[[nodiscard]] inline int get_prvalue()
{ 
	return 42; 
}

/*
[[nodiscard]] inline int && get_xvalue() // warning: returning a reference to a local object
{ 
	return 42; 
}
*/

[[nodiscard]] inline int & get_lvalue()
{
	static int x = 42; return x;
}

int main()
{
	[[maybe_unused]] double d = 0.0;

	const int i = 0;

//	int & lvalue_1 = get_prvalue(); // error: lvalue reference cannot be bound to prvalue

	[[maybe_unused]] int & lvalue_2 = get_lvalue();

//	int & lvalue_3 = 0; // error: lvalue reference cannot be bound to prvalue
//	int & lvalue_4 = d; // error: lvalue reference cannot be bound to prvalue
//	int & lvalue_5 = i; // error: lvalue reference cannot be bound to constant lvalue

	[[maybe_unused]] int && rvalue_1 = get_prvalue();

//	int && rvalue_2 = get_lvalue(); // error: rvalue reference cannot be bound to lvalue

	[[maybe_unused]] int && rvalue_3 = 0;

//	int && rvalue_4 = d; // warning: dangerous double to int conversion

//	int && rvalue_5 = i; // error: rvalue reference cannot be bound to lvalue
	
	[[maybe_unused]] const int & const_lvalue_1 = get_prvalue();
	[[maybe_unused]] const int & const_lvalue_2 = get_lvalue ();

	[[maybe_unused]] const int & const_lvalue_3 = 0;

//	const int & const_lvalue_4 = d; // warning: dangerous double to int conversion

	[[maybe_unused]] const int & const_lvalue_5 = i;
	
	[[maybe_unused]] const int && const_rvalue_1 = get_prvalue();

//	const int && const_rvalue_2 = get_lvalue(); // error: constant rvalue reference cannot be bound to lvalue
	
	[[maybe_unused]] const int && const_rvalue_3 = 0;

//	const int && const_rvalue_4 = d; // warning: dangerous double to int conversion

//	const int && const_rvalue_5 = i; // error: constant rvalue reference cannot be bound to lvalue

	return 0;
}