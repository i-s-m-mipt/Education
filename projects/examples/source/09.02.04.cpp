#include <iterator>
#include <tuple>
#include <vector>

/////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------

	auto iterator = std::begin(vector);

//  -----------------------------------------------------

	vector.resize(1'000);

//  -----------------------------------------------------

	std::ignore = *iterator; // support: -D_GLIBCXX_DEBUG
}