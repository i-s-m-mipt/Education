#include <cassert>
#include <limits>
#include <type_traits>

/////////////////////////////////////////////////////////

int main()
{
	[[maybe_unused]] char x = 'a', y = '\n', z = '\0';

//  -----------------------------------------------------

	static_assert(sizeof(char) == 1);

//  -----------------------------------------------------

	static_assert(std::is_signed_v < char > );

//  -----------------------------------------------------

	assert(std::numeric_limits < char > ::max() == +127);
		
	assert(std::numeric_limits < char > ::min() == -128);
}