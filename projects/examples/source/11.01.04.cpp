//////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <vector>

//////////////////////////////////////////////////////////////

auto generate() 
{ 
	static auto x = 0;
	
	return ++x;
}

//////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(5, 0);

//  ----------------------------------------------------------

	std::ranges::generate(vector, generate);

//  ----------------------------------------------------------

	assert(vector == std::vector < int > ({ 1, 2, 3, 4, 5 }));

//  ----------------------------------------------------------
    
    vector.clear();

//  ----------------------------------------------------------

	std::ranges::generate(vector, Functor());

//  ----------------------------------------------------------

	assert(vector == std::vector < int > ({ 1, 2, 3, 4, 5 }));
}

//////////////////////////////////////////////////////////////