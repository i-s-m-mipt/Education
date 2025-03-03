#include <iostream>

//////////////////////////////////////////////////////////////////

template < typename T > void test_v1(T)
{
	std::cout << "test_v1 (1)\n";
}

template <> void test_v1 < int > (int)
{
	std::cout << "test_v1 (2)\n";
}

void test_v1(int) 
{ 
	std::cout << "test_v1 (3)\n";
}

void test_v1(double) 
{ 
	std::cout << "test_v1 (4)\n";
}

//////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > void test_v2()
{
	std::cout << "test_v2 (1)\n";
}

//  template < typename T > void test_v2 < T, double > () // error
//  {
//	  std::cout << "test_v2 (2)\n";
//  }

//////////////////////////////////////////////////////////////////

int main()
{
    test_v1(1);

	test_v1(1.0);

	test_v1 <> (1);

	test_v1 < int > (1);

	test_v1 <> (1.0);

	test_v1 < double > (1.0);

//  ------------------------------------

	test_v2 < int, int > ();

//	test_v2 < int, double > (); // error
}