#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

int main()
{
	std::ios::sync_with_stdio(false); // support: cstdio

//  ================================================================================================

	std::istreambuf_iterator < char > istreambuf_iterator(std::cin );
	std::ostreambuf_iterator < char > ostreambuf_iterator(std::cout);

	while (istreambuf_iterator != std::istreambuf_iterator < char > ()) 
	{
		*ostreambuf_iterator++ = *istreambuf_iterator++;
	}

	std::cin.clear();

//  ================================================================================================

	std::vector < int > vector;

	std::ranges::copy(std::istream_iterator < int > (std::cin), 
					  std::istream_iterator < int > (        ), std::back_inserter(vector)); 

	std::ranges::sort(vector);

	std::ranges::copy(std::as_const(vector), std::ostream_iterator < int > (std::cout, "\n"));

	return 0;
}