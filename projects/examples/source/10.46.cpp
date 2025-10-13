////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/OpenHash.html

////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <cstddef>
#include <format>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_set>

////////////////////////////////////////////////////////////////////////////////

void show(std::unordered_set < std::string > const & set)
{
	for (auto i = 0uz; i < set.bucket_count(); ++i)
	{
		std::cout << "show : buckets[" << std::format("{:0>2}", i) << "] = {";

		for (auto iterator = set.begin(i); iterator != set.end(i); ++iterator)
		{
			std::cout << ' ' << *iterator;
		}

		std::cout << (set.bucket_size(i) > 0 ? " " : "") << "}\n\n";
	}
}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::unordered_set < std::string > set;

//  ----------------------------------------------------------------------------

	static_assert
	(
		std::is_same_v 
		< 
			decltype(set)::iterator::iterator_category, 
				
			std::forward_iterator_tag 
		> 
	);

//  ----------------------------------------------------------------------------

	show(set); set.rehash(32);

	show(set);

//  ----------------------------------------------------------------------------

	for (auto const & string : make_strings(set.bucket_count(), 5))
	{
		set.insert(string);
	}

//  ----------------------------------------------------------------------------

	show(set); set.rehash(64);
		
	show(set);

//  ----------------------------------------------------------------------------

	assert(equal(set.load_factor(), 1.0 * std::size(set) / set.bucket_count()));
}

////////////////////////////////////////////////////////////////////////////////