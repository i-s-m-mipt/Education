#include <iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost::multi_index;

struct Animal
{
	std::string name;
	std::size_t legs;
};

using animals_multi_index = multi_index_container <
	Animal, indexed_by <
	hashed_non_unique <
	member < Animal, std::string, &Animal::name > >,
	hashed_non_unique <
	member < Animal, std::size_t, &Animal::legs	> >,
	random_access <>,
	ordered_non_unique <
	member < Animal, std::size_t, &Animal::legs > > > >;

int main(int argc, char** argv)
{
	animals_multi_index animals;

	animals.insert({ "cat",    4 });
	animals.insert({ "dog",    4 });
	animals.insert({ "shark",  0 });
	animals.insert({ "spider", 8 });

	auto& hashed_legs_index = animals.get < 1 >();
	std::cout << hashed_legs_index.count(4) << std::endl;

	auto iterator = hashed_legs_index.find(0);
	hashed_legs_index.modify(iterator, [](Animal& animal) { animal.name = "whale"; });

	std::cout << hashed_legs_index.find(0)->name << std::endl;

	std::cout << std::endl;

	const auto& ordered_legs_index = animals.get < 3 >();

	auto begin = ordered_legs_index.lower_bound(4);
	auto end = ordered_legs_index.upper_bound(4);

	for (; begin != end; ++begin)
	{
		std::cout << begin->name << std::endl;
	}

	std::cout << std::endl;

	const auto& random_access_index = animals.get < 2 >();

	std::cout << random_access_index[0].name << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}