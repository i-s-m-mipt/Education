#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

//  ================================================================================================

void test_v1(benchmark::State & state)
{
    for (auto value : state)
    {
		auto size = 100'000;

        std::vector < int > vector; vector.reserve(size);

		for (auto x = 0; x < size; ++x) 
		{
			vector.push_back(x);
		}

		std::ranges::sort(vector, std::greater());

		benchmark::DoNotOptimize(vector);	
    }
}

//  ================================================================================================

void test_v2(benchmark::State & state)
{
    for (auto value : state)
    {
        std::set < int, std::greater < int > > set;

		for (auto x = 0; x < 100'000; ++x) 
		{
			set.insert(x);
		}

		benchmark::DoNotOptimize(set);	
    }
}

//  ================================================================================================

BENCHMARK(test_v1); 
BENCHMARK(test_v2); 

//  ================================================================================================

int main(int argc, char ** argv)
{
	std::set < int > set({ 1, 4, 2, 5, 3 });

	using category_t = typename decltype(set)::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::bidirectional_iterator_tag > );

//  ================================================================================================

	for (auto element : set) 
	{
		std::cout << element << ' ';
	}

	std::cout << std::endl;

//  ================================================================================================

	set.insert(std::cbegin(set), 0);

	assert(!set.insert(1).second); // support: std::multiset

	assert( set.erase(3) == 1);
	assert( set.count(3) == 0);

	assert(!set.contains(3)); // support: std::set::find

	assert(*set.lower_bound(3) == 4 && *set.upper_bound(3) == 4);
	assert(*set.lower_bound(4) == 4 && *set.upper_bound(4) == 5);

//  ================================================================================================

//	*std::begin(set) = 42; // error

	auto node = set.extract(1); node.value() = 3; set.insert(std::move(node));

//  ================================================================================================

	std::map < std::string, int > map; 

	map.insert(std::make_pair("aaaaa", 1));

//	std::begin(map)->first = "bbbbb"; // error

	map["bbbbb"] = map.at("aaaaa"); map.erase("aaaaa");

//	assert(!map.    emplace("bbbbb", 2).second); // bad
	assert(!map.try_emplace("bbbbb", 2).second);

	assert(!map.insert_or_assign("bbbbb", 2).second);

	assert(std::size(map) == 1 && map.at("bbbbb") == 2);

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();
}