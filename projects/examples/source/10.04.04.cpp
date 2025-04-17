//////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <unordered_set>

//////////////////////////////////////////////////////////////////////////

#include "08.02.09.hpp"

//////////////////////////////////////////////////////////////////////////

auto make_strings(std::size_t size_1, std::size_t size_2)
{
	std::set < std::string > strings;

	std::string string(size_2, '_');

	std::uniform_int_distribution distribution(97, 122);

	std::default_random_engine engine;
    
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

//////////////////////////////////////////////////////////////////////////

auto hash(std::string const & string) -> std::size_t
{
	std::uint32_t seed = std::size(string);

	for (auto element : string)
	{
		seed = seed << 5 ^ seed >> 27 ^ element;
	}

	return seed;
}

//////////////////////////////////////////////////////////////////////////

int main()
{	
	std::unordered_set < std::size_t > hashes;

//  ----------------------------------------------------------------------

	std::string points;

//  ----------------------------------------------------------------------

	for (auto i = 0uz; auto const & string : make_strings(1'000'000, 10))
	{
		hashes.insert(hash(string));

	//  ----------------------------------------------------
			
		if (i++ % 1'000 == 0)
		{
			points += i == 1 ? "" : ",";

			points += std::to_string(i - 1) + ',';

			points += std::to_string(i - std::size(hashes));
		}
	}

//  ----------------------------------------------------------------------
		
	Python python;

//  ----------------------------------------------------------------------

	try
	{
		auto const & local = python.local();

	//  ------------------------------------------------------------------

		boost::python::exec("from script import make_plot", local, local);

	//  ------------------------------------------------------------------

		local["make_plot"](points.c_str(), "hash");
	}
	catch (boost::python::error_already_set const &)
	{
		std::cerr << "main : " << Python::exception() << '\n';
	}
}

//////////////////////////////////////////////////////////////////////////