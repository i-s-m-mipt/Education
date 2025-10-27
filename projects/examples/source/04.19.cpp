/////////////////////////////////////////////////////////////

#include <cassert>
#include <type_traits>
#include <vector>

/////////////////////////////////////////////////////////////

constexpr auto make_integer() 
{ 
	return !std::is_constant_evaluated() ? 1 : 2;
}

/////////////////////////////////////////////////////////////

constexpr auto test_v1(int x) { return x; }

consteval auto test_v2(int x) { return x; }

/////////////////////////////////////////////////////////////

consteval auto factorial_v1(int x) -> int 
{
	return x > 1 ? x * factorial_v1(x - 1) : 1;
}

/////////////////////////////////////////////////////////////

consteval auto factorial_v2(int x)
{
    for (auto i = x - 1; i > 1; x *= i, --i);

	return x;
}

/////////////////////////////////////////////////////////////

consteval void test_v3()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };
}

/////////////////////////////////////////////////////////////

constinit auto g_x = 1;

/////////////////////////////////////////////////////////////

int main()
{
              auto x = make_integer();
    
    constexpr auto y = make_integer();

//  ---------------------------------------------------------

//  [[maybe_unused]] constexpr auto z1 = test_v1(x); // error

	[[maybe_unused]] constexpr auto z2 = test_v1(y);

//  ---------------------------------------------------------

    [[maybe_unused]]           auto z3 = test_v1(x);

    [[maybe_unused]]           auto z4 = test_v1(y);

//  ---------------------------------------------------------

//  [[maybe_unused]] constexpr auto z5 = test_v2(x); // error

	[[maybe_unused]] constexpr auto z6 = test_v2(y);

//  ---------------------------------------------------------

//  [[maybe_unused]]           auto z7 = test_v2(x); // error

	[[maybe_unused]]           auto z8 = test_v2(y);

//  ---------------------------------------------------------

    static_assert(factorial_v1(5) == 120);

    static_assert(factorial_v2(5) == 120);

//  ---------------------------------------------------------

    test_v3();

//  ---------------------------------------------------------

    assert(++g_x == 2);
}

/////////////////////////////////////////////////////////////