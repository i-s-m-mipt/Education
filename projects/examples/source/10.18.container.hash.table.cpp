#include <format>
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
	auto load_factor = static_cast < int > (std::round(unordered_set.load_factor() * 100));

	std::cout << "test : load_factor = " << load_factor << "%\n";

//  ----------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < unordered_set.bucket_count(); ++i)
	{
		std::cout << "test : buckets[" << std::format("{:0>3}", i) << "] = {";

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
	std::set < std::string > dictionary;

	std::string word(length, '_');

	std::default_random_engine engine;

	std::uniform_int_distribution distribution(97, 122);
    
	while (std::size(dictionary) < size)
    {
        for (auto & element : word) 
		{
			element = distribution(engine);
		}

		dictionary.insert(word);
    }

	return dictionary;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	using category_t = std::unordered_set < int > ::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::forward_iterator_tag > );

//  ----------------------------------------------------------------------------

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