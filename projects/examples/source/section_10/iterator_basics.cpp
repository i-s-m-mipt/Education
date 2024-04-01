#include <cassert>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

int main()
{
	const std::vector vector = { 1, 2, 3, 4, 5 };

	using category_t = typename decltype(vector)::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::random_access_iterator_tag > );

	using value_type = std::iterator_traits < decltype(vector)::iterator > ::value_type;

	static_assert(std::is_same_v < value_type, int > );

	auto begin = vector.begin(); // note: copy of begin iterator, consider std::begin

	std::advance(begin, 1); // good: better than += or -= in generic programming

	assert(*begin == 2);

	assert(*std::next(vector.begin(), 2) == 3); // good: better than + in generic programming
	assert(*std::prev(vector.end  (), 2) == 4); // good: better than - in generic programming

	for (auto iterator = vector.begin(); iterator != vector.end(); ++iterator) // note: consider std::end
	{
		std::cout << *iterator << ' ';
	}

	std::cout << std::endl;

	for (auto iterator = vector.rbegin(); iterator != vector.rend(); ++iterator) // note: reverse iterators
	{
		std::cout << *iterator << ' ';
	}

	return 0;
}