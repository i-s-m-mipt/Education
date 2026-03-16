////////////////////////////////////////////////////////////////////////////////////////

// chapter : Data Structures

////////////////////////////////////////////////////////////////////////////////////////

// section : Associative Containers

////////////////////////////////////////////////////////////////////////////////////////

// content : Associative Containers
//
// content : Containers std::map and std::multimap
//
// content : In-Place Constructors
//
// content : Object std::piecewise_construct
//
// content : Function std::forward_as_tuple
//
// content : Microbenchmarking

////////////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <string>
#include <tuple>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state) 
{
	auto argument = state.range(0);

	std::map < int, std::string > map;

	map.try_emplace(1, 1'000, 'a');

    for (auto element : state)
    {
        switch (argument)
		{
			case 1 : { map.emplace(std::make_pair(1, std::string(1'000, 'a'))); break; }

			case 2 : { map.emplace(               1, std::string(1'000, 'a') ); break; }

			case 3 :
			{ 
				map.emplace
				(
					std::piecewise_construct,

					std::forward_as_tuple(1),

					std::forward_as_tuple(1'000, 'a')
				);

				break;
			}

			case 4 :
			{
				map.try_emplace(1, 1'000, 'a');
			}
		}

        benchmark::DoNotOptimize(map);
    }
}

////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2)->Arg(3)->Arg(4);

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::map < int, std::string > map;

//  ----------------------------------------------------

	map[1] = "aaaaa";

//  ----------------------------------------------------

	map.emplace(std::make_pair(2, std::string(5, 'a')));

//  ----------------------------------------------------

	map.emplace(3, std::string(5, 'a'));

//  ----------------------------------------------------

//	map.emplace(4, 5, 'a'); // error

//  ----------------------------------------------------

	map.emplace
	(
		std::piecewise_construct,

		std::forward_as_tuple(5),

		std::forward_as_tuple(5, 'a')
	);

//  ----------------------------------------------------

	map.try_emplace(6, 5, 'a');

//  ----------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////////////////////////////////////////////////////