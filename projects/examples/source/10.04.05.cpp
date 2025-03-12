#include <cstddef>
#include <cstdint>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <unordered_set>

#include "08.02.08.hpp"

////////////////////////////////////////////////////////////////////////

auto make_strings(std::size_t size_1, std::size_t size_2)
{
	std::set < std::string > strings;

	std::string string(size_2, '_');

	std::uniform_int_distribution distribution(97, 122);

	std::default_random_engine engine;

//  ----------------------------------------------------
    
	while (std::size(strings) < size_1)
    {
        for (auto & element : string) 
		{
			element = distribution(engine);
		}

		strings.insert(string);
    }

	return strings;
}

////////////////////////////////////////////////////////////////////////

auto hash(const std::string & string) -> std::size_t
{
	std::uint32_t seed = std::size(string);

	for (auto element : string)
	{
		seed = seed << 5 ^ seed >> 27 ^ element;
	}

	return seed;
}

////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 1'000'000uz, index = 0uz;
	
	std::unordered_set < std::size_t > hashes;
		
	std::string points;

//  --------------------------------------------------------------------

	for (const auto & string : make_strings(size + 1, 10))
	{
		hashes.insert(hash(string));
			
		if (index++ % (size / 50) == 0)
		{
			points += (std::to_string(index - 1) + ',');

			points += (std::to_string(index - std::size(hashes)) + ',');
		}
	}

	points.pop_back();

//  --------------------------------------------------------------------
		
	Python python;

//  --------------------------------------------------------------------

	try
	{
		auto statement = "from 10.04.04 import make_plot";

		const auto & local = python.local();

//      --------------------------------------------------

		boost::python::exec(statement, local, local);

		local["make_plot"](points.c_str(), "hash");
	}
	catch (const boost::python::error_already_set &)
	{
		std::cerr << "main : " << Python::exception() << '\n';
	}
}