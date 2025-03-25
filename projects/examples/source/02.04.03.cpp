#include <cassert>

////////////////////////////////////////////////////////

//  auto   test_v1() { auto x = 1; return &x; } // error

//  auto & test_v2() { auto x = 1; return  x; } // error

////////////////////////////////////////////////////////

const auto & test_v3()
{
	static auto x = 0; // support : compiler-explorer.com

	return ++x;
}

////////////////////////////////////////////////////////

int main()
{
//  assert(*test_v1() == 1); // error

//	assert( test_v2() == 1); // error

//  ---------------------------------

    assert( test_v3() == 1);

    assert( test_v3() == 2);

    assert( test_v3() == 3);
}