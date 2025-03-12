#include <cassert>
#include <exception>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>

//////////////////////////////////////////////////////////////////////

int main()
{
	std::map < int, std::string > map;

//  ------------------------------------------------------------------

	try
	{
		assert(map.at(1) == "aaaaa");
	}
	catch (const std::out_of_range & exception) 
	{
		std::cerr << "main : " << exception.what() << '\n';
	}

//  ------------------------------------------------------------------

	map[1] = "aaaaa";

//  ------------------------------------------------------------------

	std::ignore = map.emplace(std::make_pair(2, std::string(5, 'b')));
	
	std::ignore = map.emplace(3, std::string(5, 'c'));

//	std::ignore = map.emplace(4, 5, 'd'); // error
	
	std::ignore = map.emplace
	(
		std::piecewise_construct, 
			
		std::forward_as_tuple(5), std::forward_as_tuple(5, 'e')
	);

//  ------------------------------------------------------------------

	std::ignore = map.try_emplace(6, 5, 'f');
}