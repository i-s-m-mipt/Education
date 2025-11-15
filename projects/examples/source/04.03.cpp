///////////////////////////////////////////////////////////////////////////////////////

#include <print>

///////////////////////////////////////////////////////////////////////////////////////

template < typename T > void test_v1           (T    ) { std::print("test_v1 (1)\n"); }

template < typename T > void test_v1           (T *  ) { std::print("test_v1 (2)\n"); }

template <            > void test_v1 < int   > (int *) { std::print("test_v1 (3)\n"); }

///////////////////////////////////////////////////////////////////////////////////////

template < typename T > void test_v2           (T    ) { std::print("test_v2 (1)\n"); }

template <            > void test_v2 < int * > (int *) { std::print("test_v2 (2)\n"); }

template < typename T > void test_v2           (T *  ) { std::print("test_v2 (3)\n"); }

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int * x = nullptr;

//  ------------------
	
	test_v1(x);

	test_v2(x);
}

///////////////////////////////////////////////////////////////////////////////////////