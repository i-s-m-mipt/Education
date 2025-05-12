/////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////

template < typename T > void handle         (T     ) { std::cout << "handle (1)\n"; }

template <            > void handle < int > (int   ) { std::cout << "handle (2)\n"; }

                        void handle         (int   ) { std::cout << "handle (3)\n"; }

                        void handle         (double) { std::cout << "handle (4)\n"; }

/////////////////////////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > void test()
{
	std::cout << "test (1)\n";
}

/////////////////////////////////////////////////////////////////////////////////////

// template < typename T > void test < T, double > () // error
// {
//     std::cout << "test (2)\n";
// }

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    handle            (1  );

	handle            (1.0);

	handle <        > (1  );

	handle < int    > (1  );

	handle <        > (1.0);

	handle < double > (1.0);

//  ---------------------------------

	test < int, int    > ();

//	test < int, double > (); // error
}

/////////////////////////////////////////////////////////////////////////////////////