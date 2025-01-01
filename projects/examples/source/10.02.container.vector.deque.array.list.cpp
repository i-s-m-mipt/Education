#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <exception>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

//  ================================================================================================

struct Entity 
{ 
	int data = 0; 
};

/////////////////////////////////////////////

int main()
{
	auto size = 5uz;

	std::vector < int > vector;

//  ================================================================================================
	
	vector.resize(2 * size); assert(std::size(vector) == size * 2 && vector.capacity() == size * 2);
	vector.resize    (size); assert(std::size(vector) == size     && vector.capacity() == size * 2);
	vector.shrink_to_fit (); assert(std::size(vector) == size     && vector.capacity() == size    );
	vector.clear         (); assert(std::size(vector) == 0        && vector.capacity() == size    );
	vector.shrink_to_fit (); assert(std::size(vector) == 0        && vector.capacity() == 0       );
	vector.reserve   (size); assert(std::size(vector) == 0        && vector.capacity() == size    );
	vector.resize    (size); assert(std::size(vector) == size     && vector.capacity() == size    );
	vector.push_back    (1); assert(std::size(vector) == size + 1 && vector.capacity() >= size + 1);
	vector.shrink_to_fit (); assert(std::size(vector) == size + 1 && vector.capacity() == size + 1);
	vector.pop_back      (); assert(std::size(vector) == size     && vector.capacity() == size + 1);
	vector.shrink_to_fit (); assert(std::size(vector) == size     && vector.capacity() == size    );

//  ================================================================================================

	try
	{
		assert(vector.at(1'000) == 0);
	}
	catch (const std::out_of_range & exception) 
	{
		std::cerr << "main : " << exception.what() << '\n';
	}

	for (auto i = 0uz; i < std::size(vector); ++i)
	{
//		assert(vector.at(i) == 0); // bad
		
		assert(vector[i] == 0);
	}

//  ================================================================================================

//	for (auto i = std:: size(vector) - 1; i >= 0; --i); // bad

	for (auto i = std::ssize(vector) - 1; i >= 0; --i);

//  ================================================================================================

	for (auto iterator = std::begin(vector); iterator != std::end(vector); ++iterator)
	{
		++(*iterator);
	}

//  ================================================================================================

	int static_array[5]{};

//	assert(static_array.size() == 5); // error

	assert(std::size (static_array) == 5);

	assert(std::begin(static_array) == static_array);

//  ================================================================================================

	std::vector < Entity > entities_1(size);

	std::vector < Entity > entities_2(std::begin(entities_1), std::end(entities_1));

	std::vector < Entity > entities_3
	(
		std::make_move_iterator(std::begin(entities_2)),
		std::make_move_iterator(std::end  (entities_2))
	);

//  ================================================================================================
	
	entities_3.insert
	(
		std::end(entities_3), std::begin(entities_1), std::next(std::begin(entities_1))
	);

	assert(std::size(entities_3) == size + 1);

	entities_3.erase(std::begin(entities_3), std::prev(std::end(entities_3), 2));

	assert(std::size(entities_3) == 2);

	entities_3.insert (std::end(entities_3), Entity(1));

	entities_3.emplace(std::end(entities_3), 1);

//  ================================================================================================

	[[maybe_unused]] auto x { 1 };

//	[[maybe_unused]] auto initializer_list_1   { 1, 2, 3, 4, 5 }; // error

	[[maybe_unused]] auto initializer_list_2 = { 1, 2, 3, 4, 5 };

	vector = { 1, 2, 3, 4, 5 };

//  ================================================================================================

	auto middle = std::size(vector) / 2;

	vector.push_back(1); vector.pop_back();

	vector.insert(          std::begin(vector),          1);
	vector.insert(std::next(std::begin(vector), middle), 1);

	vector.erase (          std::begin(vector)            );
	vector.erase (std::next(std::begin(vector), middle)   );

	std::ignore = vector[middle];

//  ================================================================================================

	std::deque < int > deque(std::begin(vector), std::end(vector));

	deque.push_back (1); deque.pop_back ();
	deque.push_front(1); deque.pop_front();

	deque.insert(std::next(std::begin(deque), middle), 1);
	deque.erase (std::next(std::begin(deque), middle)   );

	std::ignore = deque[middle];

//  ================================================================================================

	std::array < int, 5 > array({ 1, 2, 3, 4, 5 });

	std::ignore = array[middle];

	std::ignore = std::to_array(static_array);

//  ================================================================================================

	std::list < int > list_1({ 5, 3, 1, 5, 3, 1 });

//	std::ranges::sort(list_1); // error
	
	list_1.sort();

	assert(list_1.unique() == 3);

//  ================================================================================================

	std::list < int > list_2({ 4, 2, 0 });

	list_2.reverse();

	assert(list_2.remove(0) == 1);

//  ================================================================================================

	list_1.merge(list_2);

	list_2.splice
	(
				  std::begin(list_2), list_1, 
		          std::begin(list_1),
		std::next(std::begin(list_1), std::size(list_1) / 2 + 1)
	);

	assert(list_2 == std::list < int > ({ 1, 2, 3 }));

//  ================================================================================================

	std::forward_list < int > forward_list({ 1, 2, 3, 4, 5 });

	forward_list.insert_after(forward_list.before_begin(), 1);

	forward_list.erase_after(std::begin(forward_list)); 

	assert(forward_list == std::forward_list < int > ({ 1, 2, 3, 4, 5 }));

//	assert(std::size(forward_list) == 6); // error

//  ================================================================================================

	std::list < int > list_for_sort({ 5, 4, 3, 2, 1 });

//	std::ranges::sort(list_for_sort); // error

	std::vector < std::reference_wrapper < int > > wrapper
	(
		std::begin(list_for_sort), std::end(list_for_sort)
	);

	std::ranges::sort(wrapper);

	std::vector < int > result({ 1, 2, 3, 4, 5 });

	for (auto i = 0uz; i < std::size(wrapper); ++i)
	{
		assert(wrapper[i] == result[i]);
	}
}