#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

///////////////////////////////////////////////////

template < typename T > class Mean
{
public:

	void operator()(T x) 
	{ 
		m_sum += x;
		
		++m_counter;
	}

//  -----------------------------

	auto get() const 
	{ 
		return m_sum / m_counter;
	}

private:

	T m_sum = T(0);
	
	std::size_t m_counter = 0;
};

///////////////////////////////////////////////////

int main()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------

	Mean < decltype(vector)::value_type > mean;

	mean = std::ranges::for_each(vector, mean).fun;

//  -----------------------------------------------

	assert(mean.get() == 3);
}