///////////////////////////////////////////////////////////////

#include <cassert>
#include <type_traits>
#include <vector>

///////////////////////////////////////////////////////////////

constexpr auto make() 
{ 
	return !std::is_constant_evaluated() ? 1 : 2;
}

///////////////////////////////////////////////////////////////

constexpr auto handle_v1(int x) { return x; }

consteval auto handle_v2(int x) { return x; }

///////////////////////////////////////////////////////////////

consteval void test()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };
}

///////////////////////////////////////////////////////////////

constinit auto g_x = 1;

///////////////////////////////////////////////////////////////

int main()
{
              auto x = make();
    
    constexpr auto y = make();

//  -----------------------------------------------------------

//  [[maybe_unused]] constexpr auto z1 = handle_v1(x); // error

	[[maybe_unused]] constexpr auto z2 = handle_v1(y);

//  -----------------------------------------------------------

    [[maybe_unused]]           auto z3 = handle_v1(x);

    [[maybe_unused]]           auto z4 = handle_v1(y);

//  -----------------------------------------------------------

//  [[maybe_unused]] constexpr auto z5 = handle_v2(x); // error

	[[maybe_unused]] constexpr auto z6 = handle_v2(y);

//  -----------------------------------------------------------

//  [[maybe_unused]]           auto z7 = handle_v2(x); // error

	[[maybe_unused]]           auto z8 = handle_v2(y);

//  -----------------------------------------------------------

    test();

//  -----------------------------------------------------------

    assert(++g_x == 2);
}

///////////////////////////////////////////////////////////////