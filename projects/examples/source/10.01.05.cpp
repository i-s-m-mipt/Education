#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

///////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -------------------------------------------------------

	for (auto i = 0uz; i < std::size(vector); ++i)
	{		
		assert(vector[i] == static_cast < int > (i) + 1);
	}

//  -------------------------------------------------------

	try
	{
		assert(vector.at(1'000) == 1);
	}
	catch (const std::out_of_range & exception) 
	{
		std::cerr << "main : " << exception.what() << '\n';
	}
}