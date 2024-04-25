#include <cassert>
#include <iostream>
#include <iterator>
#include <string>

#include <boost/bimap.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

struct Computer { std::string name; std::size_t size{}; };

using computers_container_t = boost::multi_index::multi_index_container < Computer, 

	boost::multi_index::        indexed_by <
	boost::multi_index:: hashed_non_unique < 
	boost::multi_index::               tag < class HNU_name                         >   , 
	boost::multi_index::            member < Computer, std::string, &Computer::name > > ,
	boost::multi_index:: hashed_non_unique < 
	boost::multi_index::               tag < class HNU_size                         >   , 
	boost::multi_index::            member < Computer, std::size_t, &Computer::size > > ,
	boost::multi_index::ordered_non_unique < 
	boost::multi_index::               tag < class ONU_name                         >   , 
	boost::multi_index::            member < Computer, std::string, &Computer::name > > ,
	boost::multi_index::ordered_non_unique < 
	boost::multi_index::               tag < class ONU_size                         >   , 
	boost::multi_index::            member < Computer, std::size_t, &Computer::size > > ,
	boost::multi_index::     random_access < 
	boost::multi_index::               tag < class RA > > > > ; // note: impressed?

int main()
{
	computers_container_t computers;

	computers.insert({ "alpha", 4 });
	computers.insert({ "betta", 2 });
	computers.insert({ "gamma", 4 });
	computers.insert({ "delta", 8 });

	auto & HNU_name_index = computers.get < HNU_name > ();
	auto & HNU_size_index = computers.get < HNU_size > ();
	auto & ONU_name_index = computers.get < ONU_name > ();
	auto & ONU_size_index = computers.get < ONU_size > ();

	assert(HNU_name_index.contains("alpha")); // note: smth like std::unordered_multiset

	HNU_size_index.modify(HNU_size_index.find(2), [](auto && computer)  constexpr { computer.name = "bravo"; });

	assert(HNU_size_index.find(2)->name == "bravo");

	assert(ONU_name_index.contains("alpha")); // note: smth like std::multiset

	for (auto begin  = ONU_size_index.lower_bound(4); 
		      begin != ONU_size_index.upper_bound(4); ++begin)
	{
		assert(begin->size == 4);
	}

	assert(computers.get < RA > ()[0].name == "alpha"); // note: smth like std::vector
	
	boost::bimap < std::string, std::size_t > bimap; // note: consider boost::bimaps::(multi)set_of

	bimap.insert({ "alpha", 4 });
	bimap.insert({ "betta", 2 });
	bimap.insert({ "gamma", 4 }); // note: duplicate
	bimap.insert({ "delta", 8 });

	assert(bimap.left. count("alpha") == 1); // good: O(log(N)) complexity search by key
	assert(bimap.right.count(      4) == 1); // good: O(log(N)) complexity search by value

	for (const auto & element : bimap)
	{
		std::cout << element.left << " has size of " << element.right << std::endl;
	}

	return 0;
}