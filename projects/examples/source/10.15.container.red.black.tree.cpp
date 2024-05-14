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

void test_1(benchmark::State & state) // complexity: O(N * log(N))
{
    for (auto _ : state)
    {
        std::vector < int > vector; vector.reserve(state.range(0));

		for (auto x = 0; x < state.range(0); ++x) { vector.push_back(x); }

		std::ranges::sort(vector, std::greater());

		benchmark::DoNotOptimize(vector);	
    }
}

//  ================================================================================================

void test_2(benchmark::State & state) // complexity: O(N * log(N))
{
    for (auto _ : state)
    {
        std::set < int, std::greater < int > > set;

		for (auto x = 0; x < state.range(0); ++x) { set.insert(x); }

		benchmark::DoNotOptimize(set);	
    }
}

//  ================================================================================================

BENCHMARK(test_1)->Arg(100'000); 
BENCHMARK(test_2)->Arg(100'000); 

//  ================================================================================================

int main(int argc, char ** argv)
{
	std::set < int > set { 1, 4, 2, 5, 3 }; // complexity: O(log(N))

	using category_t = typename decltype(set)::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::bidirectional_iterator_tag > );

//  ================================================================================================

	for (const auto element : set) std::cout << element << ' ';

	std::cout << std::endl;

//  ================================================================================================

	set.insert(std::cbegin(set), 0); // complexity: O(1)

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

	std::map < std::string, int > map; // complexity: O(log(N))

	map.insert(std::make_pair("hello", 41)); 

//	std::begin(map)->first = "world"; // error

	map["world"] = map.at("hello"); map.erase("hello");

//	assert(!map.    emplace("world", 42).second); // bad
	assert(!map.try_emplace("world", 42).second);

	assert(!map.insert_or_assign("world", 42).second);

	assert(std::size(map) == 1 && map.at("world") == 42);

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}