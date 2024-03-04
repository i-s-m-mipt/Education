#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

int main() // good: feel strength and elegance of this example
{
	std::vector < int > vector;

	std::ranges::copy(
		std::istream_iterator < int > (std::cin),
		std::istream_iterator < int > (),
			std::back_inserter(vector));

	std::ranges::sort(vector);

	std::ranges::unique_copy(std::as_const(vector),
		std::ostream_iterator < int > (std::cout, "\n"));

	return 0;
}