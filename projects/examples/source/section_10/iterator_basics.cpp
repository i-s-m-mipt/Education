#include <cassert>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

int main()
{
	std::vector v({ 1, 2, 3, 4, 5 });

	using category_t = typename decltype(v)::iterator::iterator_category;

	static_assert(std::is_same_v < category_t, std::random_access_iterator_tag > );

	auto begin = v.begin(); // note: copy of begin iterator

	std::advance(begin, 1); // good: better than += or -= in generic programming

	assert(*begin == 2);

	assert(*std::next(v.begin(), 2) == 3); // good: better than + in generic programming
	assert(*std::prev(v.end  (), 2) == 4); // good: better than - in generic programming

	for (auto iterator = v.begin(); iterator != v.end(); ++iterator)
	{
		std::cout << *iterator << ' ';
	}

	std::cout << std::endl;

	for (auto iterator = v.rbegin(); iterator != v.rend(); ++iterator) // note: reverse iterators
	{
		std::cout << *iterator << ' ';
	}

	return 0;
}