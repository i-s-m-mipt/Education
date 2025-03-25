#include <cassert>
#include <exception>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>

///////////////////////////////////////////////////////////////

int main()
{
	std::map < int, std::string > map;

//  -----------------------------------------------------------

	map[1] = "aaaaa";

//  -----------------------------------------------------------

	map.emplace(std::make_pair(2, std::string(5, 'b')));
	
	map.emplace(3, std::string(5, 'c'));

//	map.emplace(4, 5, 'd'); // error
	
	map.emplace
	(
		std::piecewise_construct, 
			
		std::forward_as_tuple(5), std::forward_as_tuple(5, 'e')
	);

//  -----------------------------------------------------------

	map.try_emplace(6, 5, 'f');
}