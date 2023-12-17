#include <array>
#include <cassert>
#include <deque>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
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
	[[maybe_unused]] auto single_value { 42 }; // note: auto -> int

	auto initializer_list = { 1, 2, 3, 4, 5 }; // note: auto -> std::initializer_list < int >

	std::vector < int > vector(initializer_list); // note: constructor for initializer_list

	constexpr std::size_t size = 5; // good: use alias std::size_t for sizes and indexes

	std::vector < int > v; 
	
	v.resize(size * 2); assert(v.size() == size * 2 && v.capacity() == size * 2);
	v.resize(size);     assert(v.size() == size     && v.capacity() == size * 2);
	v.shrink_to_fit();  assert(v.size() == size     && v.capacity() == size    );
	v.clear();          assert(v.size() == 0        && v.capacity() == size    );
	v.shrink_to_fit();  assert(v.size() == 0        && v.capacity() == 0       );
	v.reserve(size);    assert(v.size() == 0        && v.capacity() == size    );
	v.resize(size);     assert(v.size() == size     && v.capacity() == size    );
	v.push_back(42);    assert(v.size() == size + 1 && v.capacity() >= size + 1);
	v.shrink_to_fit();  assert(v.size() == size + 1 && v.capacity() == size + 1);
	v.pop_back();       assert(v.size() == size     && v.capacity() == size + 1);
	v.shrink_to_fit();  assert(v.size() == size     && v.capacity() == size    );

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

	for (auto iterator = std::begin(v); iterator != std::end(v); ++iterator)
	{
		++(*iterator); // note: use iterators as high-level pointers in containers
	}

	std::vector < Data > v1(size);
	std::vector < Data > v2(std::cbegin(v1), std::cend(v1)); // note: copy sequence
	std::vector < Data > v3(
		std::make_move_iterator(std::cbegin(v1)),
		std::make_move_iterator(std::cend  (v1))); // note: move sequence
	
	v3.insert(std::cend(v3), std::begin(v2), std::next(std::begin(v2), 2));

	assert(std::size(v3) == size + 2);

	v3.erase(std::cbegin(v3), std::prev(std::cend(v3), 2));

	assert(std::size(v3) == 2);

	Data data('a', 42, 3.14);

	v1.push_back(std::move(data)); // note: additional copy or move constructor call

	v1.emplace_back('a', 42, 3.14); // good: forwarding arguments to constructor

	std::array < int, size > array = {1, 2, 3, 4, 5}; // note: aggregate as static array

//	array.push_back(42); // error: static array, fixed size

	std::deque < int > deque(std::cbegin(vector), std::cend(vector));

	deque.push_front(42); // note: O(1) complexity as push_back

	return 0;
}