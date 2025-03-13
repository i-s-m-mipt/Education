#include <iostream>
#include <type_traits>

/////////////////////////////////////////////////////////////////////

void test_v1() 
{ 
	std::cout << "test_v1\n";
}

/////////////////////////////////////////////////////////////////////

void test_v2(void(*function)()) 
{ 
	std::cout << "test_v2\n";
	
	function();
}

/////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(std::is_same_v < decltype( test_v1), void   () > );

	static_assert(std::is_same_v < decltype(&test_v1), void(*)() > );

//  -----------------------------------------------------------------

	test_v2(test_v1);
}