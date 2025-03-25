#include <cassert>
#include <type_traits>

///////////////////////////////////////////////////////////

int main()
{
	auto x = 1, & y = x; // support : compiler-explorer.com

	static_assert(std::is_same_v < decltype(y), int & > );

	assert(y == x);

//  -------------------------------------------------------

//	[[maybe_unused]] int & z; // error
}