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
	constexpr std::size_t size = 5; // good: use alias std::size_t for sizes and indexes

	std::vector < int > vector; 

//  ================================================================================================
	
	vector.resize(2 * size); assert(std::size(vector) == size * 2 && vector.capacity() == size * 2);
	vector.resize    (size); assert(std::size(vector) == size     && vector.capacity() == size * 2);
	vector.shrink_to_fit (); assert(std::size(vector) == size     && vector.capacity() == size    );
	vector.clear         (); assert(std::size(vector) == 0        && vector.capacity() == size    );
	vector.shrink_to_fit (); assert(std::size(vector) == 0        && vector.capacity() == 0       );
	vector.reserve   (size); assert(std::size(vector) == 0        && vector.capacity() == size    );
	vector.resize    (size); assert(std::size(vector) == size     && vector.capacity() == size    );
	vector.push_back   (42); assert(std::size(vector) == size + 1 && vector.capacity() >= size + 1); // note: not +1
	vector.shrink_to_fit (); assert(std::size(vector) == size + 1 && vector.capacity() == size + 1);
	vector.pop_back      (); assert(std::size(vector) == size     && vector.capacity() == size + 1);
	vector.shrink_to_fit (); assert(std::size(vector) == size     && vector.capacity() == size    );

	std::cout << vector.max_size() << std::endl; // note: std::length_error if size > max size

//  ================================================================================================

	try
	{
		assert(vector.at(666) == 0); // note: use at() if index wasn't verified at all
	}
	catch (...) {}

	for (std::size_t i = 0; i < std::size(vector); ++i) // good: std::size instead of member
	{
		assert(vector[i] == 0); // note: use operator[] if index was verified elsewhere
	}

//  ================================================================================================

	for (auto i = std::ssize(vector) - 1; i >= 0; --i) // good: signed index, no infinite loop
	{
		assert(vector[i] == 0);
	}

//  ================================================================================================

	for (auto iterator = std::begin(vector); iterator != std::end(vector); ++iterator) // note: RBF
	{
		++(*iterator); // note: use iterators as high-level pointers in containers
	}

//  ================================================================================================

	constexpr int static_array[size]{};

//	assert(static_array.size() == size); // error: not a class

	assert(std::size (static_array) == size);

	assert(std::begin(static_array) == static_array);

//  ================================================================================================

	std::vector < Data > vector_1(size);
	std::vector < Data > vector_2(std::cbegin(vector_1), std::cend(vector_1)); // note: copy container

//	*std::cbegin(v) = 42; // error: constant iterator

	std::vector < Data > vector_3(std::make_move_iterator(std::begin(vector_1)),
								  std::make_move_iterator(std::end  (vector_1))); // note: move container

//  ================================================================================================
	
	vector_3.insert(std::cend(vector_3), std::cbegin(vector_2), std::next(std::cbegin(vector_2), 2));

	assert(std::size(vector_3) == size + 2);

	vector_3.erase(std::cbegin(vector_3), std::prev(std::cend(vector_3), 2));

	assert(std::size(vector_3) == 2);

	Data data('a', 42, 3.14);

	vector_1.push_back(std::move(data)); // note: additional copy or move constructor call

	vector_1.emplace_back('a', 42, 3.14); // good: forwarding arguments to constructor

//  ================================================================================================

	[[maybe_unused]] constexpr auto single_value { 42 }; // note: auto -> int

	const auto initializer_list = { 1, 2, 3, 4, 5 }; // note: auto -> std::initializer_list < int >

	vector = initializer_list; // note: constructors and assignment operators for initializer_list

//  ================================================================================================

	const auto middle = std::size(vector) / 2;

	vector.push_back(42); // good: O(1) complexity (amortized)

	vector.insert(          std::cbegin(vector),          42); // note: O(N) complexity 
	vector.insert(std::next(std::cbegin(vector), middle), 42); // note: O(N) complexity

	vector.pop_back(); // good: O(1) complexity 

	vector.erase(          std::cbegin(vector)         ); // note: O(N) complexity 
	vector.erase(std::next(std::cbegin(vector), middle)); // note: O(N) complexity

	[[maybe_unused]] const auto vector_value = vector[middle]; // good: O(1) complexity

//  ================================================================================================

	std::deque < int > deque(std::cbegin(vector), std::cend(vector));

	deque.push_back (42); // good: O(1) complexity (amortized)
	deque.push_front(42); // good: O(1) complexity (amortized)

	deque.insert(std::next(std::cbegin(deque), middle), 42); // note: O(N) complexity

	deque.pop_back (); // good: O(1) complexity 
	deque.pop_front(); // good: O(1) complexity

	deque.erase(std::next(std::cbegin(deque), middle)); // note: O(N) complexity

	[[maybe_unused]] const auto deque_value = deque[middle]; // good: O(1) complexity

//  ================================================================================================

	constexpr std::array < int, size > array { 1, 2, 3, 4, 5 }; // note: aggregate initialization

	[[maybe_unused]] const auto array_value = array[middle]; // good: O(1) complexity, fast on stack

	[[maybe_unused]] constexpr auto array_from_static_array = std::to_array(static_array);

//  ================================================================================================

	std::list < int > list_1 { 8, 0, 6, 2, 4, 4, 2, 6, 0, 8 };
	
	list_1.sort(); // note: std::sort is unacceptable due to bidirectional iterators

	assert(list_1.unique() == 5); // note: erases all consecutive duplicate elements

//  ================================================================================================

	std::list < int > list_2 { 9, 7, 5, 3, 1, 42 };

	list_2.reverse(); // note: reverses the order of the elements in the container

	assert(list_2.remove(42) == 1); // note: erases all elements that are equal 42

//  ================================================================================================

	list_1.merge(list_2); // note: list_1 contains 0 1 2 3 4 5 6 7 8 9

	list_2.splice(std::begin(list_2), list_1, 
		          std::begin(list_1),
		std::next(std::begin(list_1), std::size(list_1) / 2));

	for (const auto element : list_2) std::cout << element << ' ';

	std::cout << std::endl;

//  ================================================================================================

	std::forward_list < int > forward_list { 1, 2, 3, 4, 5 }; // note: forward iterators

	forward_list.insert_after(forward_list.before_begin(), 42);

	forward_list.push_front(43); // note: no push_back member function

	forward_list.erase_after(std::begin(forward_list)); 

	for (const auto element : forward_list) std::cout << element << ' ';

	std::cout << std::endl;

//	assert(std::size(forward_list) == 6); // error: forward_list has no size() member

//  ================================================================================================

	std::list < int > list_for_sort { 2, 4, 1, 5, 3 };

	std::vector < std::reference_wrapper < int > > wrapper(std::begin(list_for_sort), std::end(list_for_sort));

	std::ranges::sort(wrapper); // note: cannot sort list directly due to bidirectional iterators

	for (const auto element : wrapper) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}