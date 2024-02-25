#include <cassert>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>

int main()
{
	std::list < int > list_1 = { 8, 0, 6, 2, 4, 4, 2, 6, 0, 8 };
	
	list_1.sort(); // note: std::sort is unacceptable due to bidirectional iterators

	assert(list_1.unique() == 5); // note: erases all consecutive duplicate elements

	std::list < int > list_2 = { 9, 7, 5, 3, 1, 42 };

	list_2.reverse(); // note: reverses the order of the elements in the container

	assert(list_2.remove(42) == 1); // note: erases all elements that are equal 42

	list_1.merge(list_2); // note: { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } in list_1

	list_2.splice(std::begin(list_2), list_1, 
		          std::begin(list_1),
		std::next(std::begin(list_1), std::size(list_1) / 2));

	for (auto element : list_2) std::cout << element << ' '; // note: outputs 0 1 2 3 4

	std::cout << std::endl;

	std::forward_list < int > forward_list = { 1, 2, 3, 4, 5 }; // note: forward iterators

	forward_list.insert_after(forward_list.before_begin(), 42);

	forward_list.push_front(43); // note: no push_back member function

	forward_list.erase_after(std::begin(forward_list)); 

	for (auto element : forward_list) std::cout << element << ' '; // note: outputs 43 1 2 3 4 5

	std::cout << std::endl;

//	assert(std::size(forward_list) == 6); // error: forward_list has no size() member

	return 0;
}