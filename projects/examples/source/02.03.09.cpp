#include <cassert>
#include <type_traits>

////////////////////////////////////////////////////////////

int main()
{
	auto x = 1, & r_x = x; // support: compiler-explorer.com

	static_assert(std::is_same_v < decltype(r_x), int & > );

	assert(r_x == x);

//  --------------------------------------------------------

//	[[maybe_unused]] int & ref; // error
}