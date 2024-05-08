#include <iostream>

//  ================================================================================================

[[nodiscard]] inline int    get_prvalue() {                    return 42; }
[[nodiscard]] inline int &  get__lvalue() { static int x = 42; return  x; }

//  ================================================================================================

int main()
{
	double d = 3.14; const int i = 42;

//  ================================================================================================

//	[[maybe_unused]] int &  lvalue_1 = get_prvalue(); // error

	[[maybe_unused]] int &  lvalue_2 = get__lvalue();

//	[[maybe_unused]] int &  lvalue_3 = d; // error

//	[[maybe_unused]] int &  lvalue_4 = i; // error

//  ================================================================================================

	[[maybe_unused]] int && rvalue_1 = get_prvalue();

//	[[maybe_unused]] int && rvalue_2 = get__lvalue(); // error

	[[maybe_unused]] int && rvalue_3 = d;

//	[[maybe_unused]] int && rvalue_4 = i; // error

//  ================================================================================================
	
	[[maybe_unused]] const int &  const_lvalue_1 = get_prvalue();

	[[maybe_unused]] const int &  const_lvalue_2 = get__lvalue();

	[[maybe_unused]] const int &  const_lvalue_3 = d;

	[[maybe_unused]] const int &  const_lvalue_4 = i;

//  ================================================================================================
	
	[[maybe_unused]] const int && const_rvalue_1 = get_prvalue();

//	[[maybe_unused]] const int && const_rvalue_2 = get__lvalue(); // error

	[[maybe_unused]] const int && const_rvalue_3 = d;

//	[[maybe_unused]] const int && const_rvalue_4 = i; // error

	return 0;
}