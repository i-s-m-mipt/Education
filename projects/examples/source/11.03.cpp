///////////////////////////////////////////////////////////////////

// chapter : Programming with Algorithms

///////////////////////////////////////////////////////////////////

// content : Functors and Predicates
//
// content : Function States
//
// content : User-Defined Functors and Predicates
//
// content : Operator ()
//
// content : Algorithms std::ranges::generate and std::ranges::fill

///////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <vector>

///////////////////////////////////////////////////////////////////

auto make_integer()
{
	static auto x = 0;

	return ++x;
}

///////////////////////////////////////////////////////////////////

class Functor
{
public :

	auto operator()()
	{
		return ++m_x;
	}

private :

	int m_x = 0;
};

///////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(5, 0);

//  ----------------------------------------------------------

	std::ranges::generate(vector, make_integer);

//  ----------------------------------------------------------

	assert(vector == std::vector < int > ({ 1, 2, 3, 4, 5 }));

//  ----------------------------------------------------------

	std::ranges::fill(vector, 0);

//  ----------------------------------------------------------

	std::ranges::generate(vector, Functor());

//  ----------------------------------------------------------

	assert(vector == std::vector < int > ({ 1, 2, 3, 4, 5 }));
}

///////////////////////////////////////////////////////////////////