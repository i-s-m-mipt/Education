#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    for (auto element : state)
    {
        std::vector < int > vector; 

		for (auto i = 1'000; i > 0; --i) 
		{
			vector.push_back(i);
		}

		std::ranges::sort(vector);

		benchmark::DoNotOptimize(vector);	
    }
}

///////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    for (auto element : state)
    {
        std::set < int > set;

		for (auto i = 1'000; i > 0; --i) 
		{
			set.insert(i);
		}

		benchmark::DoNotOptimize(set);	
    }
}

///////////////////////////////////////////////////////////////////////////////////

void test_v3(benchmark::State & state)
{
    for (auto element : state)
    {
        std::set < int > set;

		auto iterator = std::begin(set);

		for (auto i = 1'000; i > 0; --i) 
		{
			set.insert(iterator, i);

			iterator = std::begin(set);
		}

		benchmark::DoNotOptimize(set);	
    }
}

///////////////////////////////////////////////////////////////////////////////////

void test_v4(benchmark::State & state)
{
    for (auto element : state)
    {
        std::set < int > set;

		auto iterator = std::begin(set);

		for (auto i = 1'000; i > 0; --i) 
		{
			set.insert(iterator, i);

			iterator = std::end(set);
		}

		benchmark::DoNotOptimize(set);	
    }
}

///////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1); 
BENCHMARK(test_v2); 
BENCHMARK(test_v3);
BENCHMARK(test_v4);

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	using category_t = std::set < int > ::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::bidirectional_iterator_tag > );

//  -------------------------------------------------------------------------------

	std::set < int > set = { 5, 4, 3, 2, 1 }; 
	
	assert(std::ranges::is_sorted(set));

//  -------------------------------------------------------------------------------

	assert( set.count(1) == 1 && set.find(1) != std::end(set) && set.contains(1));

	assert( set.erase(1) == 1 && set.insert(1).second);

	assert(*set.lower_bound(1) == 1);
	
	assert(*set.upper_bound(1) == 2);

//  -------------------------------------------------------------------------------

//	*std::begin(set) = 2; // error

	auto node = set.extract(1); node.value() = 2; set.insert(std::move(node));

//  -------------------------------------------------------------------------------

	std::map < int, std::string > map; 

	try
	{
		assert(map.at(1) == "aaaaa");
	}
	catch (const std::out_of_range & exception) 
	{
		std::cerr << "main : " << exception.what() << '\n';
	}

	map[1] = "aaaaa";

	map.emplace(std::make_pair(2, std::string(5, 'b')));
 
    map.emplace(3, std::string(5, 'c'));

//	map.emplace(4, 5, 'd'); // error
 
    map.emplace
	(
		std::piecewise_construct, 
		
		std::forward_as_tuple(5), 

		std::forward_as_tuple(5, 'e')
	);

    map.try_emplace(6, 5, 'f');

//  -------------------------------------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}