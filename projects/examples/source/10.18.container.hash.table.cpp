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
		std::cout << "chaining method : doubly-linked list\n";
	}
	else
	{
		std::cout << "chaining method : singly-linked list\n";
	}

	std::cout << std::endl;

	for (auto i = 0uz; i < unordered_set.bucket_count(); ++i)
	{
		std::cout << "bucket[" << std::setw(3) << std::setfill('0') << std::right << i << "]: ";

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
	std::unordered_set < int > unordered_set;

	unordered_set.rehash(64);

	std::mt19937_64 engine{ std::random_device()() };

	std::uniform_int_distribution distribution(100, 999);

	for (auto i = 0uz; i < unordered_set.bucket_count(); ++i)
	{
		unordered_set.insert(distribution(engine));
	}

	print(unordered_set); unordered_set.rehash(65);
	print(unordered_set);
}