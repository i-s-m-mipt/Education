#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iterator>
#include <set>
#include <vector>

//////////////////////////////////////////////////////////////////////////

auto test() 
{ 
	static auto x = 0;
	
	return ++x;
}

//////////////////////////////////////////////////////////////////////////

class Functor
{
public:

	auto operator()() 
	{ 
		return ++m_data;
	}

private:

	int m_data = 0;
};

//////////////////////////////////////////////////////////////////////////

template < typename T > class Mean
{
public:

	void operator()(T x) 
	{ 
		m_sum += x;
		
		++m_counter;
	}

	auto get() const 
	{ 
		return m_sum / m_counter;
	}

private:

	T m_sum = T(0);
	
	std::size_t m_counter = 0;
};

//////////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		std::ranges::sort(vector, std::greater());

		assert(std::ranges::is_sorted(vector, std::greater()));
	}
	
//  ----------------------------------------------------------------------

	{
		std::set < int, std::greater < int > > set = { 1, 2, 3, 4, 5 };

		assert(std::ranges::is_sorted(set, std::greater()));
	}	

//  ----------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		std::ranges::transform(vector, std::begin(vector), std::negate());

		assert(vector == std::vector < int > ({ -1, -2, -3, -4, -5 }));
	}

//  ----------------------------------------------------------------------

	{
		auto size = 5uz;

		std::vector < int > vector_1(size, 0), vector_2(size, 0);

		std::ranges::generate(vector_1, test);

		std::ranges::generate(vector_2, Functor());

		for (auto i = 0uz; i < size; ++i)
		{
			assert(vector_1[i] == vector_2[i]);
		}
	}

//  ----------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		Mean < decltype(vector)::value_type > mean;

		mean = std::ranges::for_each(vector, mean).fun;

		assert(mean.get() == 3);
	}
}