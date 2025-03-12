#include <initializer_list>
#include <vector>

//////////////////////////////////////////////////////////////

int main()
{
	[[maybe_unused]] auto x { 1 };

//  ----------------------------------------------------------

	[[maybe_unused]] auto list_1 = { 1 };

	[[maybe_unused]] auto list_2 = { 1, 2, 3, 4, 5 };

//	[[maybe_unused]] auto list_3   { 1, 2, 3, 4, 5 }; // error

//  ----------------------------------------------------------

	std::vector < int > vector = list_2;
}