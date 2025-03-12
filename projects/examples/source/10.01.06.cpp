#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////

int main()
{
	bool array[5]{};

	static_assert(sizeof(array) == 5);

//  ------------------------------------------------------------------------------

	std::vector < bool > vector(1'000'000'000, false);
 
	auto proxy = vector.front();

	static_assert(!std::is_same_v < decltype(proxy), bool > );

	std::ignore = static_cast < bool > (vector.front());

//  ------------------------------------------------------------------------------

	std::cout << "main : enter char to continue : "; auto x = '\0'; std::cin >> x;
}