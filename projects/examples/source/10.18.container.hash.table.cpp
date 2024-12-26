#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <type_traits>
#include <unordered_set>

//////////////////////////////////////////////////////////////////////////////////////////////////

void test(const std::unordered_set < int > & unordered_set)
{
	std::cout << "test : unordered_set.load_factor() = ";
	
	std::cout << static_cast < int > (unordered_set.load_factor() * 100) << "%\n";

//  ----------------------------------------------------------------------------------------------

	using iterator_category_t = typename std::unordered_set < int > ::iterator::iterator_category;

	static_assert(std::is_same_v < iterator_category_t, std::forward_iterator_tag > );

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

int main()
{
	std::unordered_set < int > unordered_set;

	test(unordered_set); unordered_set.rehash(32);

	test(unordered_set);

	std::default_random_engine engine;

	std::uniform_int_distribution distribution(100, 999);

	for (auto i = 0uz; i < unordered_set.bucket_count(); ++i)
	{
		unordered_set.insert(distribution(engine));
	}

	test(unordered_set); unordered_set.rehash(64);
	
	test(unordered_set);
}