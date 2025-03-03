#include <iostream>

//////////////////////////////////////////

template < typename T > void test_v1(T)
{
	std::cout << "test_v1 (1)\n";
}

template < typename T > void test_v1(T *)
{
	std::cout << "test_v1 (2)\n";
}

template <> void test_v1 < int > (int *)
{ 
	std::cout << "test_v1 (3)\n";
} 

//////////////////////////////////////////

template < typename T > void test_v2(T)
{
	std::cout << "test_v2 (1)\n";
}

template <> void test_v2 < int * > (int *)
{ 
	std::cout << "test_v2 (2)\n";
} 

template < typename T > void test_v2(T *)
{
	std::cout << "test_v2 (3)\n";
}

//////////////////////////////////////////

int main()
{
    int * ptr = nullptr;

//  --------------------
	
	test_v1(ptr);

	test_v2(ptr);
}