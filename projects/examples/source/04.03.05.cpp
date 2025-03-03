#include <cassert>
#include <type_traits>
#include <vector>

/////////////////////////////////////////////////////////////

constexpr auto test_v1() 
{ 
	return std::is_constant_evaluated() ? 1 : 2;
}

/////////////////////////////////////////////////////////////

constexpr auto test_v2(int x) { return x; }

consteval auto test_v3(int x) { return x; }

/////////////////////////////////////////////////////////////

consteval void test_v4()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };
}

/////////////////////////////////////////////////////////////

constinit auto g_x = 1;

/////////////////////////////////////////////////////////////

int main()
{
    constexpr auto x = test_v1(); 
    
              auto y = test_v1();

//  ---------------------------------------------------------

    [[maybe_unused]] constexpr auto z1 = test_v2(x);

//	[[maybe_unused]] constexpr auto z2 = test_v2(y); // error

//  ---------------------------------------------------------

    [[maybe_unused]]           auto z3 = test_v2(x);

    [[maybe_unused]]           auto z4 = test_v2(y);

//  ---------------------------------------------------------

    [[maybe_unused]] constexpr auto z5 = test_v3(x);

//	[[maybe_unused]] constexpr auto z6 = test_v3(y); // error

//  ---------------------------------------------------------

    [[maybe_unused]]           auto z7 = test_v3(x);

//	[[maybe_unused]]           auto z8 = test_v3(y); // error

//  ---------------------------------------------------------

    test_v4();

//  ---------------------------------------------------------

    assert(++g_x == 2);
}