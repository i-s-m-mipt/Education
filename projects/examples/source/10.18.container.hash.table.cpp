#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <type_traits>
#include <unordered_set>

//  ================================================================================================

void print(const std::unordered_set < int > & unordered_set)
{
	std::cout << "N objects       : " << unordered_set.            size() << std::endl;
	std::cout << "N objects (max) : " << unordered_set.        max_size() << std::endl;
	std::cout << "M buckets       : " << unordered_set.    bucket_count() << std::endl;
	std::cout << "M buckets (max) : " << unordered_set.max_bucket_count() << std::endl;
	std::cout << "L = N / M       : " << unordered_set.     load_factor() << std::endl;
	std::cout << "L = N / M (max) : " << unordered_set. max_load_factor() << std::endl;

	using category_t = typename std::unordered_set < int > ::iterator::iterator_category;
	
	if (std::is_same_v < category_t, std::bidirectional_iterator_tag > )
	{
		std::cout << "chaining method : doubly-linked list" << std::endl;
	}
	else
	{
		std::cout << "chaining method : singly-linked list" << std::endl;
	}

	std::cout << std::endl;

	for (std::size_t i = 0; i < unordered_set.bucket_count(); ++i)
	{
		std::cout << "bucket[" << std::setw(3) << std::right << std::setfill('0') << i << "]: ";

		for (auto iterator = unordered_set.begin(i); iterator != unordered_set.end(i); ++iterator)
		{
			std::cout << *iterator << ' ';
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

//  ================================================================================================

int main()
{
	std::unordered_set < int > unordered_set; // note: O(1) complexity (amortized) for operations

	unordered_set.rehash(64); // note: creates at least 64 buckets

	std::mt19937_64 engine{ std::random_device()() };

	std::uniform_int_distribution distribution(100, 999);

	for (std::size_t i = 0; i < unordered_set.bucket_count(); ++i)
	{
		unordered_set.insert(distribution(engine));
	}

	print(unordered_set);

	unordered_set.rehash(128); // note: creates at least 128 buckets

	print(unordered_set);

	return 0;
}