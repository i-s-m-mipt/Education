#include <cassert>
#include <limits>
#include <type_traits>

/////////////////////////////////////////////////////////

// support : en.wikipedia.org/wiki/ASCII

/////////////////////////////////////////////////////////

int main()
{
	[[maybe_unused]] char x = 'a', y = '\0', z = '\n';

//  -----------------------------------------------------

	static_assert(sizeof(char) == 1);

//  -----------------------------------------------------

	static_assert(std::is_signed_v < char > );

//  -----------------------------------------------------

	assert(std::numeric_limits < char > ::max() == +127);
		
	assert(std::numeric_limits < char > ::min() == -128);
}