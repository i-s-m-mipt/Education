#include <cassert>
#include <cstddef>
#include <iostream>
#include <type_traits>

////////////////////////////////////////////////////////////

int main()
{
    auto x = 1, * p_x = &x;

	static_assert(std::is_same_v < decltype(p_x), int * > );

	assert(*p_x == x);

	std::cout << "main : p_x = " << p_x << '\n';	

//  --------------------------------------------------------

	[[maybe_unused]] int * ptr = nullptr;

//	[[maybe_unused]] int * ptr = NULL; // bad
}