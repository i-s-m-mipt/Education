#include <format>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_set>

//////////////////////////////////////////////////////////////////////////////

void test(const std::unordered_set < std::string > & set)
{
	auto rate = static_cast < int > (std::round(set.load_factor() * 100));

//  --------------------------------------------------------------------------

	std::cout << "test : rate = " << rate << "%\n";

//  --------------------------------------------------------------------------

	for (auto i = 0uz; i < set.bucket_count(); ++i)
	{
		std::cout << "test : buckets[" << std::format("{:0>2}", i) << "] = {";

		for (auto iterator = set.begin(i); iterator != set.end(i); ++iterator)
		{
			std::cout << ' ' << *iterator;
		}

		std::cout << (set.bucket_size(i) > 0 ? " " : "") << "}\n";
	}
}

//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////

int main()
{
	std::unordered_set < std::string > set;

//  -----------------------------------------------------------------

	test(set); set.rehash(32);

	test(set);

//  -----------------------------------------------------------------

	for (const auto & string : make_strings(set.bucket_count(), 5))
	{
		set.insert(string);
	}

//  -----------------------------------------------------------------

	test(set); set.rehash(64);
	
	test(set);

//  -----------------------------------------------------------------

	static_assert
	(
		std::is_same_v 
		< 
			std::unordered_set < int > ::iterator::iterator_category, 
				
			std::forward_iterator_tag 
		> 
	);
}