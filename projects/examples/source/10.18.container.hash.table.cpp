#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_set>

//////////////////////////////////////////////////////////////////////////////////////////////////

void test(const std::unordered_set < std::string > & unordered_set)
{
	using iterator_category_t = decltype(std::begin(unordered_set))::iterator_category;

	static_assert(std::is_same_v < iterator_category_t, std::forward_iterator_tag > );

//  ----------------------------------------------------------------------------------------------
	
	std::cout << "test : unordered_set.load_factor() = ";
	
	std::cout << static_cast < int > (unordered_set.load_factor() * 100) << "%\n";

//  ----------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < unordered_set.bucket_count(); ++i)
	{
		std::cout << "test : buckets[";
		
		std::cout << std::setw(3) << std::setfill('0') << std::right << i << "] = {";

		for (auto iterator = unordered_set.begin(i); iterator != unordered_set.end(i); ++iterator)
		{
			std::cout << ' ' << *iterator;
		}

		std::cout << (unordered_set.bucket_size(i) > 0 ? " " : "") << "}\n";
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

auto make_dictionary(std::size_t size, std::size_t length)
{
    std::default_random_engine engine;

	std::uniform_int_distribution distribution(97, 122);
	
	std::set < std::string > dictionary;
    
	for (std::string word(length, '_'); std::size(dictionary) < size; dictionary.insert(word))
    {
        for (auto & element : word) 
		{
			element = distribution(engine);
		}
    }

	return dictionary;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::unordered_set < std::string > unordered_set;

	test(unordered_set); unordered_set.rehash(32);

	test(unordered_set);

	for (const auto & word : make_dictionary(unordered_set.bucket_count(), 5))
	{
		unordered_set.insert(word);
	}

	test(unordered_set); unordered_set.rehash(64);
	
	test(unordered_set);
}