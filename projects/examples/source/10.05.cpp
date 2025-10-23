////////////////////////////////////////////////////////////

#include <cassert>
#include <cstdio>
#include <print>
#include <stdexcept>
#include <vector>

////////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  --------------------------------------------------------

	for (auto i = 0uz; i < std::size(vector); ++i)
	{		
		assert(vector[i] == static_cast < int > (i) + 1);
	}

//  --------------------------------------------------------

	try
	{
		assert(vector.at(5) == 0);
	}
	catch (std::out_of_range const & exception) 
	{
		std::print(stderr, "main : {}\n", exception.what());
	}
}

////////////////////////////////////////////////////////////