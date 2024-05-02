#include <cstdint>
#include <exception>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_set>

#include "16.04.embedding.python.header.hpp"

//  ================================================================================================

std::set < std::string > make_random_words(std::size_t size, const std::size_t length)
{
    std::mt19937_64 engine(std::random_device{}());

	std::uniform_int_distribution <> distribution(97, 122);
	
	std::set < std::string > words;
    
	for (std::string word(length, '_'); std::size(words) < size; words.insert(word))
    {
        for (auto & letter : word) letter = distribution(engine);
    }

	return words;
}

//  ================================================================================================

std::size_t hash_DEK(std::string_view string) // note: Donald E. Knuth implementation
{
	std::uint32_t hash = std::size(string); // note: as with x86 build to make collisions

	for (const auto letter : string)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ letter;
	}

	return hash;
}

//  ================================================================================================

int main()
{
    try
    {
        Python python;

//  ================================================================================================

        boost::python::exec("from script import factorial", python.global(), python.global());
		
		std::cout << boost::python::extract < std::string > (
            python.global()["factorial"](100))() << std::endl; // note: outputs 100!

//  ================================================================================================

        const std::size_t size = 1'000'000, length = 10, step = size / 50;

        std::unordered_set < std::size_t > hashes; std::size_t index = 0; std::string points;

        for (const auto & word : make_random_words(size + 1, length))
        {
            if (hashes.insert(hash_DEK(word)); index++ % step == 0)
            {
                points += std::to_string(index - 1                ) + ',' + 
                          std::to_string(index - std::size(hashes)) + ',';
            }
        }

        points.pop_back(); // note: remove last comma in string

//  ================================================================================================

        boost::python::exec("from script import make_plot", python.global(), python.global());
		
		python.global()["make_plot"](points.c_str(), "DEK");
    }
    catch (const boost::python::error_already_set &)
	{
		std::cerr << Python::exception() << '\n';
	}
    catch (const std::exception & exception)
    {
        std::cerr << exception.what() << '\n';
    }
    
    return 0;
}