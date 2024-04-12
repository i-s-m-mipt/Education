#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

// =================================================================================================

[[nodiscard]] inline int f() noexcept // note: different functions have same types
{
	static auto state = 0; // note: internal state, see reference arguments

	return (state++);
}

// =================================================================================================

class C // note: different classes have different types
{
public:

	[[nodiscard]] constexpr int operator()() const noexcept { return (m_state++); }

private:

	mutable int m_state = 0; // note: internal state, see logical constancy

}; // class C

// =================================================================================================

template < typename T > class Sum
{
public:

	constexpr void operator()(T x) noexcept { s += x; }

	[[nodiscard]] constexpr T result() const noexcept { return s; }

private:

	T s = T();

}; // template < typename T > class Sum

// =================================================================================================

template < typename T > class Mean
{
public:

	constexpr void operator()(T x) noexcept { ++n; s += x; }

	[[nodiscard]] constexpr T result() const noexcept { return (s / n); }

private:

	std::size_t n = 0; T s = T();

}; // class Mean

// =================================================================================================

int main()
{
	std::vector < int > vector_1 = { 1, 4, 2, 5, 3 };

	std::ranges::sort(vector_1                ); // note: sort range in  ascending order
	std::ranges::sort(vector_1, std::greater()); // note: sort range in descending order

	const std::set < int, std::greater < int > > set = { 1, 4, 2, 5, 3 };

	for (const auto element : set) std::cout << element << ' ';

	std::cout << std::endl;

	constexpr std::size_t size = 5;

	constexpr C c; // note: functional object with overloaded operator()

	std::vector < int > vector_2(size, 0); 
	std::vector < int > vector_3(size, 0); 

	std::ranges::generate(vector_2, f); // note: generate elements in range
	std::ranges::generate(vector_3, c); // note: generate elements in range

	for (std::size_t i = 0; i < size; ++i)
	{
		assert(vector_2[i] == static_cast < int > (i));
		assert(vector_3[i] == static_cast < int > (i));
	}

	Sum < int > sum;

	sum = std::ranges::for_each(std::as_const(vector_2), sum).fun; // note: sum elements in range
	sum = std::ranges::for_each(std::as_const(vector_3), sum).fun; // note: sum elements in range

	assert(sum.result() == 20);

	std::ranges::transform(
		std::as_const(vector_2), std::begin(vector_2), std::negate()); // note: transform 1 range(s) to range

	std::ranges::transform(
		std::as_const(vector_2), 
		std::as_const(vector_3), std::begin(vector_3), std::  plus()); // note: transform 2 range(s) to range

	for (const auto element : vector_3) assert(element == 0);

	Mean < decltype(vector_1)::value_type > mean;

	mean = std::ranges::for_each(std::as_const(vector_1), mean).fun; // note: sum and count elements in range

	assert(mean.result() == 3); 

	return 0;
}