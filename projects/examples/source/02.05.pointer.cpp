#include <iostream>

int main()
{
	int  x = 42; int * ptr_x = &x; ++(*ptr_x);
	auto y = 42; auto  ptr_y = &y; ++(*ptr_y); // note: * inside auto

	std::cout << ptr_x << ' ' << *ptr_x << std::endl;
	std::cout << ptr_y << ' ' << *ptr_y << std::endl;

//  ================================================================================================

	int * ptr_null_1 = nullptr; // good: nullptr instead of 0 or NULL

	[[maybe_unused]] auto ptr_null_2 = nullptr; // note: auto -> std::nullptr_t

//	*ptr_null_1 = 42; // error: dereference null pointer

	if (ptr_null_1) // good: verify pointer before dereference
	{
		std::cout << *ptr_null_1 << std::endl;
	}

//  ================================================================================================

		  auto z1 = 42; 
	const auto z2 = 42; // note: consider with pointers to constant objects

//  ================================================================================================

	[[maybe_unused]] const int * ptr_cz1_1 = &z1;
	[[maybe_unused]] int const * ptr_cz1_2 = &z1; // note: same as ptr_cz1_1

//	*ptr_cz1_1 = 42; // error: constant object
//	*ptr_cz1_2 = 42; // error: constant object

	[[maybe_unused]] const int * ptr_cz2_1 = &z2;
	[[maybe_unused]] auto        ptr_cz2_2 = &z2; // note: same as ptr_cz2_1

//	*ptr_cz2_1 = 42; // error: constant object
//	*ptr_cz2_2 = 42; // error: constant object

//  ================================================================================================

	[[maybe_unused]] int * const cptr_z1_1 = &z1;
	[[maybe_unused]] const auto  cptr_z1_2 = &z1; // note: same as cptr_z1_1

//	cptr_z1_1 = nullptr; // error: constant pointer
//	cptr_z1_2 = nullptr; // error: constant pointer

//	int * ptr_z2 = &z2; // error: pointer to non-constant object

//  ================================================================================================

	[[maybe_unused]] const int * const cptr_cz1_1 = &z1;
	[[maybe_unused]] const auto        cptr_cz1_2 = &z1;

	[[maybe_unused]] const int * const cptr_cz2_1 = &z2;
	[[maybe_unused]] const auto        cptr_cz2_2 = &z2;

	return 0;
}