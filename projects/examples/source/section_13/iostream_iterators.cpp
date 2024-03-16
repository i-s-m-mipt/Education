#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

int main() // good: feel strength and elegance of this example
{
	std::vector < int > vector;

	using input_iterator = std::istream_iterator < int > ; // note: input only iterator

	std::ranges::copy(input_iterator(std::cin), input_iterator(), std::back_inserter(vector)); 

	std::ranges::sort(vector);

	using output_iterator = std::ostream_iterator < int > ; // note: output only iterator

	std::ranges::unique_copy(std::as_const(vector), output_iterator(std::cout, "\n"));

	return 0;
}