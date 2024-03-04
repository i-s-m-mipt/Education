#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

[[nodiscard]] auto f() noexcept // note: different functions have same types
{
	static auto state = 0; // note: internal state, see reference arguments

	return (state++);
}

class C // note: different classes have different types
{
public:

	[[nodiscard]] auto operator()() const noexcept { return (m_state++); }

private:

	mutable int m_state = 0; // note: internal state, see logical constancy

}; // class C

template < typename T > class Sum
{
public:

	void operator()(T x) noexcept { s += x; }

	[[nodiscard]] auto result() const noexcept { return s; }

private:

	T s = T();

}; // template < typename T > class Sum

template < typename T > class Mean
{
public:

	void operator()(T x) noexcept { ++n; s += x; }

	[[nodiscard]] auto result() const noexcept { return (s / n); }

private:

	std::size_t n = 0; T s = T();

}; // class Mean

int main()
{
	std::vector < int > v1 = { 1, 4, 2, 5, 3 };

	std::ranges::sort(v1                ); // note: 1 2 3 4 5
	std::ranges::sort(v1, std::greater()); // note: 5 4 3 2 1

	std::set < int, std::greater < int > > set = { 1, 4, 2, 5, 3 };

	for (auto element : set) std::cout << element << ' '; // note: outputs 5 4 3 2 1

	std::cout << std::endl;

	const std::size_t size = 5;

	C c; // note: functional object with overloaded operator()

	std::vector < int > v2(size, 0); std::ranges::generate(v2, f); // note: slower
	std::vector < int > v3(size, 0); std::ranges::generate(v3, c); // note: faster

	for (std::size_t i = 0; i < size; ++i)
	{
		assert(v2[i] == static_cast < int > (i));
		assert(v3[i] == static_cast < int > (i));
	}

	Sum < int > sum;

	sum = std::move(std::ranges::for_each(std::as_const(v2), sum).fun);
	sum = std::move(std::ranges::for_each(std::as_const(v3), sum).fun);

	assert(sum.result() == 20);

	std::ranges::transform(std::as_const(v2),                    std::begin(v2), std::negate());
	std::ranges::transform(std::as_const(v2), std::as_const(v3), std::begin(v3), std::  plus());

	for (auto element : v3) assert(element == 0);

	assert(std::ranges::for_each(std::as_const(v1), Mean < decltype(v1)::value_type > ()).fun.result() == 3);

	return 0;
}