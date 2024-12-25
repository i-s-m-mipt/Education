#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <iterator>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

int main()
{
	std::ios::sync_with_stdio(false);

//  --------------------------------------------------------------------------

	std::cout << "Enter 1 or more characters and Ctrl + D : ";

	std::cout.flush();

	std::ostreambuf_iterator < char > ostreambuf_iterator(std::cout);

	for (auto element : "\nEntered characters : ")
	{
		*ostreambuf_iterator++ = element;
	}

	std::istreambuf_iterator < char > istreambuf_iterator(std::cin);

	while (istreambuf_iterator != std::istreambuf_iterator < char > ()) 
	{
		*ostreambuf_iterator++ = *istreambuf_iterator++;
	}

	*ostreambuf_iterator = '\n';

	std::cin.clear();

//  --------------------------------------------------------------------------

	std::cout << "Enter 1 or more integers and 1 non-integer : ";

	std::vector < int > vector;

	std::ranges::copy
	(
		std::istream_iterator < int > (std::cin),

		std::istream_iterator < int > (), 
		
		std::back_inserter(vector)
	);

	std::cin.clear(); char c; std::cin >> c;

	std::cout << "vector = { ";

	std::ranges::copy(vector, std::ostream_iterator < int > (std::cout, " "));

	std::cout << "}\n";
}