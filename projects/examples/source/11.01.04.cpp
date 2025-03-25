#include <algorithm>
#include <cassert>
#include <vector>

///////////////////////////////////////////////

auto test() 
{ 
	static auto x = 0;
	
	return ++x;
}

///////////////////////////////////////////////

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

///////////////////////////////////////////////

int main()
{
    auto size = 5uz;

//  -------------------------------------------

	std::vector < int > vector_1(size, 0);
    
    std::vector < int > vector_2(size, 0);

//  -------------------------------------------

	std::ranges::generate(vector_1, test);

	std::ranges::generate(vector_2, Functor());

//  -------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		assert(vector_1[i] == vector_2[i]);
	}
}