#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <iterator>
#include <vector>

class Data
{
public:

	Data() = default;

	explicit Data(char c, int i, double d) noexcept : m_c(c), m_i(i), m_d(d) {}

private:

	char m_c; int m_i; double m_d;

}; // class Data

int main()
{
	const std::size_t size = 5; // good: use alias std::size_t for sizes and indexes

	std::vector < int > v; 
	
	v.resize(2 * size); assert(v.size() == size * 2 && v.capacity() == size * 2);
	v.resize    (size); assert(v.size() == size     && v.capacity() == size * 2);
	v.shrink_to_fit (); assert(v.size() == size     && v.capacity() == size    );
	v.clear         (); assert(v.size() == 0        && v.capacity() == size    );
	v.shrink_to_fit (); assert(v.size() == 0        && v.capacity() == 0       );
	v.reserve   (size); assert(v.size() == 0        && v.capacity() == size    );
	v.resize    (size); assert(v.size() == size     && v.capacity() == size    );
	v.push_back   (42); assert(v.size() == size + 1 && v.capacity() >= size + 1); // note: not +1
	v.shrink_to_fit (); assert(v.size() == size + 1 && v.capacity() == size + 1);
	v.pop_back      (); assert(v.size() == size     && v.capacity() == size + 1);
	v.shrink_to_fit (); assert(v.size() == size     && v.capacity() == size    );

	std::cout << v.max_size() << std::endl;

	try
	{
		assert(v.at(666) == 0); // note: use at() if index wasn't verified at all
	}
	catch (...) {}

	for (std::size_t i = 0; i < std::size(v); ++i)
	{
		assert(v[i] == 0); // note: use operator[] if index was verified elsewhere
	}

	for (auto i = std::ssize(v) - 1; i >= 0; --i) // good: signed index, no infinite loop
	{
		assert(v[i] == 0);
	}

	for (auto iterator = std::begin(v); iterator != std::end(v); ++iterator)
	{
		++(*iterator); // note: use iterators as high-level pointers in containers
	}

	int static_array[size]{};

//	assert(static_array.size() == size); // error: not a class

	assert(std::size(static_array) == size);

	assert(std::begin(static_array) == static_array);

	std::vector < Data > v1(size);
	std::vector < Data > v2(std::cbegin(v1), std::cend(v1)); // note: copy collection

//	*std::cbegin(v) = 42; // error: constant iterator

	std::vector < Data > v3(
		std::make_move_iterator(std::begin(v1)),
		std::make_move_iterator(std::end  (v1))); // note: move collection
	
	v3.insert(std::cend(v3), std::cbegin(v2), std::next(std::cbegin(v2), 2));

	assert(std::size(v3) == size + 2);

	v3.erase(std::cbegin(v3), std::prev(std::cend(v3), 2));

	assert(std::size(v3) == 2);

	Data data('a', 42, 3.14);

	v1.push_back(std::move(data)); // note: additional copy or move constructor call

	v1.emplace_back('a', 42, 3.14); // good: forwarding arguments to constructor

	[[maybe_unused]] auto single_value { 42 }; // note: auto -> int

	auto initializer_list = { 1, 2, 3, 4, 5 }; // note: auto -> std::initializer_list < int >

	std::vector < int > vector(initializer_list); // note: constructor for initializer_list

	const auto middle = std::size(vector) / 2;

	vector.push_back(42); // good: O(1) complexity (amortized)

	vector.insert(          std::cbegin(vector),          42); // note: O(N) complexity 
	vector.insert(std::next(std::cbegin(vector), middle), 42); // note: O(N) complexity

	vector.pop_back(); // good: O(1) complexity 

	vector.erase(          std::cbegin(vector)         ); // note: O(N) complexity 
	vector.erase(std::next(std::cbegin(vector), middle)); // note: O(N) complexity

	[[maybe_unused]] auto vector_value = vector[middle]; // good: O(1) complexity

	std::deque < int > deque(std::cbegin(vector), std::cend(vector));

	deque.push_back (42); // good: O(1) complexity (amortized)
	deque.push_front(42); // good: O(1) complexity (amortized)

	deque.insert(std::next(std::cbegin(deque), middle), 42); // note: O(N) complexity

	deque.pop_back (); // good: O(1) complexity 
	deque.pop_front(); // good: O(1) complexity

	deque.erase(std::next(std::cbegin(deque), middle)); // note: O(N) complexity

	[[maybe_unused]] auto deque_value = deque[middle]; // good: O(1) complexity

	std::array < int, size > array = { 1, 2, 3, 4, 5 }; // note: aggregate initialization

	[[maybe_unused]] auto array_value = array[middle]; // good: O(1) complexity, fast on stack

	[[maybe_unused]] auto array_from_static_array = std::to_array(static_array);

	return 0;
}