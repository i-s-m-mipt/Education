#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <type_traits>
#include <unordered_set>

//////////////////////////////////////////////////////////////////////////////////////////////////

void test(const std::unordered_set < int > & unordered_set)
{
	std::cout << "N objects       = " << unordered_set.            size() << '\n';
	std::cout << "N objects (max) = " << unordered_set.        max_size() << '\n';
	std::cout << "M buckets       = " << unordered_set.    bucket_count() << '\n';
	std::cout << "M buckets (max) = " << unordered_set.max_bucket_count() << '\n';
	std::cout << "L = N / M       = " << unordered_set.     load_factor() << '\n';
	std::cout << "L = N / M (max) = " << unordered_set. max_load_factor() << '\n';

//  ----------------------------------------------------------------------------------------------

	using iterator_category_t = typename std::unordered_set < int > ::iterator::iterator_category;

	static_assert(std::is_same_v < iterator_category_t, std::forward_iterator_tag > );

//  ----------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < unordered_set.bucket_count(); ++i)
	{
		std::cout << "bucket[" << std::setw(3) << std::setfill('0') << std::right << i << "] = {";

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