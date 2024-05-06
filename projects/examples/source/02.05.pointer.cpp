#include <iostream>

int main()
{
	int  x = 42; int * ptr_x = &x; ++(*ptr_x);
	auto y = 42; auto  ptr_y = &y; ++(*ptr_y);

	std::cout << ptr_x << ' ' << *ptr_x << std::endl;
	std::cout << ptr_y << ' ' << *ptr_y << std::endl;

//  ================================================================================================

	int * ptr_null_1 = nullptr; // note: см. NULL

	[[maybe_unused]] auto ptr_null_2 = nullptr;

//	*ptr_null_1 = 42; // error: разыменование нулевого указателя

	if (ptr_null_1) std::cout << *ptr_null_1 << std::endl;

//  ================================================================================================

		  auto z1 = 42; 
	const auto z2 = 42;

//  ================================================================================================

	[[maybe_unused]] const int * ptr_cz1_1 = &z1;
	[[maybe_unused]] int const * ptr_cz1_2 = &z1;

//	*ptr_cz1_1 = 42; // error: константный объект
//	*ptr_cz1_2 = 42; // error: константный объект

	[[maybe_unused]] const int * ptr_cz2_1 = &z2;
	[[maybe_unused]] auto        ptr_cz2_2 = &z2;

//	*ptr_cz2_1 = 42; // error: константный объект
//	*ptr_cz2_2 = 42; // error: константный объект

//  ================================================================================================

//	int * ptr_z2 = &z2; // error: указатель на неконстантный объект

	[[maybe_unused]] int * const cptr_z1_1 = &z1;
	[[maybe_unused]] const auto  cptr_z1_2 = &z1;

//	cptr_z1_1 = nullptr; // error: константный указатель
//	cptr_z1_2 = nullptr; // error: константный указатель

//  ================================================================================================

	[[maybe_unused]] const int * const cptr_cz1_1 = &z1;
	[[maybe_unused]] const auto        cptr_cz1_2 = &z1;

	[[maybe_unused]] const int * const cptr_cz2_1 = &z2;
	[[maybe_unused]] const auto        cptr_cz2_2 = &z2;

	return 0;
}