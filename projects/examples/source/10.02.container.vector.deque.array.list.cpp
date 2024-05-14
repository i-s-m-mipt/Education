#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>
#include <vector>

//  ================================================================================================

class Data
{
public:

	constexpr Data() noexcept = default;

	constexpr explicit Data(char c, int i, double d) noexcept : m_c(c), m_i(i), m_d(d) {}

private:

	char m_c{}; int m_i{}; double m_d{};

}; // class Data

//  ================================================================================================

int main()
{
	constexpr std::size_t size = 5;

	std::vector < int > vector;

//  ================================================================================================
	
	vector.resize(2 * size); assert(std::size(vector) == size * 2 && vector.capacity() == size * 2);
	vector.resize    (size); assert(std::size(vector) == size     && vector.capacity() == size * 2);
	vector.shrink_to_fit (); assert(std::size(vector) == size     && vector.capacity() == size    );
	vector.clear         (); assert(std::size(vector) == 0        && vector.capacity() == size    );
	vector.shrink_to_fit (); assert(std::size(vector) == 0        && vector.capacity() == 0       );
	vector.reserve   (size); assert(std::size(vector) == 0        && vector.capacity() == size    );
	vector.resize    (size); assert(std::size(vector) == size     && vector.capacity() == size    );
	vector.push_back   (42); assert(std::size(vector) == size + 1 && vector.capacity() >= size + 1);
	vector.shrink_to_fit (); assert(std::size(vector) == size + 1 && vector.capacity() == size + 1);
	vector.pop_back      (); assert(std::size(vector) == size     && vector.capacity() == size + 1);
	vector.shrink_to_fit (); assert(std::size(vector) == size     && vector.capacity() == size    );

	std::cout << vector.max_size() << std::endl; // support: std::length_error

//  ================================================================================================

	try
	{
		assert(vector.at(666) == 0);
	}
	catch (...) {}

	for (std::size_t i = 0; i < std::size(vector); ++i)
	{
//		assert(vector.at(i) == 0); // bad
		assert(vector   [i] == 0);
	}

//  ================================================================================================

//	for (auto i = std:: size(vector) - 1; i >= 0; --i) {} // bad

	for (auto i = std::ssize(vector) - 1; i >= 0; --i)
	{
		assert(vector[i] == 0);
	}

//  ================================================================================================

	for (auto iterator = std::begin(vector); iterator != std::end(vector); ++iterator)
	{
		++(*iterator);
	}

//  ================================================================================================

	constexpr int static_array[size]{};

//	assert(static_array.size() == size); // error

	assert(std::size (static_array) == size);

	assert(std::begin(static_array) == static_array);

//  ================================================================================================

	std::vector < Data > vector_1(size);
	std::vector < Data > vector_2(std::cbegin(vector_1), std::cend(vector_1));

//	*std::cbegin(v) = 42; // error

	std::vector < Data > vector_3(std::make_move_iterator(std::begin(vector_1)),
								  std::make_move_iterator(std::end  (vector_1)));

//  ================================================================================================
	
	vector_3.insert(std::cend(vector_3), std::cbegin(vector_2), std::next(std::cbegin(vector_2), 2));

	assert(std::size(vector_3) == size + 2);

	vector_3.erase(std::cbegin(vector_3), std::prev(std::cend(vector_3), 2));

	assert(std::size(vector_3) == 2);

	Data data('a', 42, 3.14);

	vector_1.push_back(std::move(data));

	vector_1.emplace_back('a', 42, 3.14);

//  ================================================================================================

	[[maybe_unused]] constexpr auto single_value { 42 }; // detail: int

	const auto initializer_list = { 1, 2, 3, 4, 5 }; // detail: std::initializer_list < int >

	vector = initializer_list;

//  ================================================================================================

	const auto middle = std::size(vector) / 2;

	vector.push_back(42); // complexity: O(1)
	vector. pop_back(  ); // complexity: O(1)

	vector.insert(          std::cbegin(vector),          42); // complexity: O(N)
	vector.insert(std::next(std::cbegin(vector), middle), 42); // complexity: O(N)

	vector.erase (          std::cbegin(vector)             ); // complexity: O(N)
	vector.erase (std::next(std::cbegin(vector), middle)    ); // complexity: O(N)

	[[maybe_unused]] const auto vector_value = vector[middle]; // complexity: O(1)

//  ================================================================================================

	std::deque < int > deque(std::cbegin(vector), std::cend(vector));

	deque. push_back(42); // complexity: O(1)
	deque.  pop_back(  ); // complexity: O(1)

	deque.push_front(42); // complexity: O(1)
	deque. pop_front(  ); // complexity: O(1)

	deque.insert(std::next(std::cbegin(deque), middle), 42); // complexity: O(N)
	deque.erase (std::next(std::cbegin(deque), middle)    ); // complexity: O(N)

	[[maybe_unused]] const auto deque_value = deque[middle]; // complexity: O(1)

//  ================================================================================================

	constexpr std::array < int, size > array { 1, 2, 3, 4, 5 };

	[[maybe_unused]] const auto array_value = array[middle]; // complexity: O(1)

	[[maybe_unused]] constexpr auto array_from_static_array = std::to_array(static_array);

//  ================================================================================================

	std::list < int > list_1 { 8, 0, 6, 2, 4, 4, 2, 6, 0, 8 };

//	std::ranges::sort(list_1); // error
	
	list_1.sort();

	assert(list_1.unique() == 5);

//  ================================================================================================

	std::list < int > list_2 { 9, 7, 5, 3, 1, 42 };

	list_2.reverse();

	assert(list_2.remove(42) == 1);

//  ================================================================================================

	list_1.merge(list_2); // elements: { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }

	list_2.splice(std::begin(list_2), list_1, 
		          std::begin(list_1),
		std::next(std::begin(list_1), std::size(list_1) / 2));

	for (const auto element : list_2) std::cout << element << ' ';

	std::cout << std::endl;

//  ================================================================================================

	std::forward_list < int > forward_list { 1, 2, 3, 4, 5 };

	forward_list.insert_after(forward_list.before_begin(), 42);

	forward_list.push_front(42);

	forward_list.erase_after(std::begin(forward_list)); 

	for (const auto element : forward_list) std::cout << element << ' ';

	std::cout << std::endl;

//	assert(std::size(forward_list) == 6); // error

//  ================================================================================================

	std::list < int > list_for_sort { 2, 4, 1, 5, 3 };

//	std::ranges::sort(list_for_sort); // error

	std::vector < std::reference_wrapper < int > > wrapper(std::begin(list_for_sort), 
														   std::end  (list_for_sort));

	std::ranges::sort(wrapper);

	for (const auto element : wrapper) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}