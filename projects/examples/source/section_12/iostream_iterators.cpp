#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() // good: feel strength and elegance of this example
{
	std::vector < int > vector;

	std::copy(
		std::istream_iterator < int > (std::cin),
		std::istream_iterator < int > (),
			std::back_inserter(vector));

	std::sort(std::begin(vector), std::end(vector));

	std::unique_copy(std::cbegin(vector), std::cend(vector),
		std::ostream_iterator < int > (std::cout, "\n"));

	return 0;
}