#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

//  ================================================================================================

[[nodiscard]] inline int f() noexcept { static auto state = 0; return (state++); }

//  ================================================================================================

class C
{
public:

	[[nodiscard]] constexpr int operator()() const noexcept { return (m_state++); }

private:

	mutable int m_state = 0;

}; // class C

//  ================================================================================================

template < typename T > class Sum
{
public:

	constexpr void operator()(T x) noexcept { s += x; }

	[[nodiscard]] constexpr T result() const noexcept { return s; }

private:

	T s = T();

}; // template < typename T > class Sum

//  ================================================================================================

template < typename T > class Mean
{
public:

	constexpr void operator()(T x) noexcept { ++n; s += x; }

	[[nodiscard]] constexpr T result() const noexcept { return (s / n); }

private:

	std::size_t n = 0; T s = T();

}; // class Mean

//  ================================================================================================

int main()
{
	std::vector < int > vector_1 { 1, 4, 2, 5, 3 };

	std::ranges::sort(vector_1                );
	std::ranges::sort(vector_1, std::greater());

//  ================================================================================================

	const std::set < int, std::greater < int > > set { 1, 4, 2, 5, 3 };

	for (const auto element : set) std::cout << element << ' ';

	std::cout << std::endl;

//  ================================================================================================

	constexpr std::size_t size = 5;

	constexpr C c;

	std::vector < int > vector_2(size, 0); 
	std::vector < int > vector_3(size, 0); 

	std::ranges::generate(vector_2, f);
	std::ranges::generate(vector_3, c);

	for (std::size_t i = 0; i < size; ++i)
	{
		assert(vector_2[i] == static_cast < int > (i));
		assert(vector_3[i] == static_cast < int > (i));
	}

//  ================================================================================================

	Sum < int > sum;

	sum = std::ranges::for_each(std::as_const(vector_2), sum).fun;
	sum = std::ranges::for_each(std::as_const(vector_3), sum).fun;

	assert(sum.result() == 20);

//  ================================================================================================

	std::ranges::transform(std::as_const(vector_2), 
						   std::   begin(vector_2), std::negate());

	std::ranges::transform(std::as_const(vector_2), 
						   std::as_const(vector_3), 
						   std::   begin(vector_3), std::  plus());

	for (const auto element : vector_3) assert(element == 0);

//  ================================================================================================

	Mean < decltype(vector_1)::value_type > mean;

	mean = std::ranges::for_each(std::as_const(vector_1), mean).fun;

	assert(mean.result() == 3); 

	return 0;
}