#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iterator>
#include <set>
#include <vector>

//  ================================================================================================

auto generator_v1() 
{ 
	static auto state = 0; 
	
	return ++state; 
}

//  ================================================================================================

class Generator_v2
{
public:

	auto operator()() 
	{ 
		return ++m_state; 
	}

private:

	int m_state = 0;
};

//  ================================================================================================

template < typename T > class Sum
{
public:

	void operator()(T x) 
	{ 
		m_sum += x; 
	}

	auto get() const 
	{ 
		return m_sum; 
	}

private:

	T m_sum = T(0);
};

//  ================================================================================================

template < typename T > class Mean
{
public:

	void operator()(T x) 
	{ 
		m_sum += x; ++m_counter;
	}

	auto get() const 
	{ 
		return m_sum / m_counter; 
	}

private:

	T m_sum = T(0); std::size_t m_counter = 0;
};

//  ================================================================================================

int main()
{
	std::vector < int > vector_1({ 1, 2, 3, 4, 5 });

	std::ranges::sort(vector_1, std::ranges::greater());

	assert(std::ranges::is_sorted(vector_1, std::ranges::greater()));

//  ================================================================================================

	std::set < int, std::ranges::greater > set({ 1, 2, 3, 4, 5 });

	assert(std::ranges::is_sorted(set, std::ranges::greater()));

//  ================================================================================================

	auto size = 5uz;

	std::vector < int > vector_2(size, 0); 
	std::vector < int > vector_3(size, 0); 

	std::ranges::generate(vector_2, generator_v1  );
	std::ranges::generate(vector_3, Generator_v2());

	for (auto i = 0uz; i < size; ++i)
	{
		assert(vector_2[i] == static_cast < int > (i + 1));
		assert(vector_3[i] == static_cast < int > (i + 1));
	}

//  ================================================================================================

	Sum < int > sum;

	sum = std::ranges::for_each(vector_2, sum).fun;
	sum = std::ranges::for_each(vector_3, sum).fun;

	assert(sum.get() == 30);

//  ================================================================================================

	std::ranges::transform(vector_2,           std::begin(vector_2), std::negate());
	std::ranges::transform(vector_2, vector_3, std::begin(vector_3), std::plus  ());

	for (auto element : vector_3) 
	{
		assert(element == 0);
	}

//  ================================================================================================

	Mean < decltype(vector_1)::value_type > mean;

	mean = std::ranges::for_each(vector_1, mean).fun;

	assert(mean.get() == 3); 
}