#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <iterator>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::ios::sync_with_stdio(false);
	}

//  ------------------------------------------------------------------------------

	{
		std::cout << "main : enter chars and Ctrl + D : ";

		std::cout.flush();

		std::ostreambuf_iterator < char > iterator_1(std::cout);

		std::istreambuf_iterator < char > iterator_2(std::cin );

		for (auto element : "\nmain : std::cout.streambuf = ")
		{
			*iterator_1++ = element;
		}		

		while (iterator_2 != std::istreambuf_iterator < char > ()) 
		{
			*iterator_1++ = *iterator_2++;
		}

		*iterator_1 = '\n'; std::cin.clear();
	}

//  ------------------------------------------------------------------------------

	{
		std::cout << "main : enter ints and non-int : ";

		std::vector < int > vector;

		std::ranges::copy
		(
			std::istream_iterator < int > (std::cin),

			std::istream_iterator < int > (), 
			
			std::back_inserter(vector)
		);

		std::cin.clear(); auto x = '\0'; std::cin >> x;

		std::cout << "main : vector = { ";

		std::ranges::copy(vector, std::ostream_iterator < int > (std::cout, " "));

		std::cout << "}\n";
	}
}