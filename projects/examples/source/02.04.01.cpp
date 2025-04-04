//////////////////////////////////////////////////////////////////

// support : en.wikipedia.org/wiki/X86_calling_conventions

//////////////////////////////////////////////////////////////////

#include <iostream>
#include <tuple>

//////////////////////////////////////////////////////////////////

[[nodiscard]] auto test_v1(int x);

//////////////////////////////////////////////////////////////////

[[nodiscard]] auto test_v1(int x) 
{
	return x;
}

//////////////////////////////////////////////////////////////////

void test_v2(int x, int y = 0)
{ 
	std::cout << "test_v2 : x = " << x << " y = " << y << '\n';
}

//////////////////////////////////////////////////////////////////

// void test_v3(int x = 0, int y) // error
// { 
//     std::cout << "test_v3 : x = " << x << " y = " << y << '\n';
// }

//////////////////////////////////////////////////////////////////

int main()
{
//	test_v1(1); // error

//  -------------------------------------------------

    [[maybe_unused]] auto x = test_v1(1);

//  -------------------------------------------------

    std::ignore = test_v1(1);

//  -------------------------------------------------

    test_v2(1   );

    test_v2(1, 2); // support : compiler-explorer.com
}

//////////////////////////////////////////////////////////////////