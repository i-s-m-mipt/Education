#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////

template < typename F1, typename F2, typename F3 > auto bind(F1 && f1, F2 && f2, F3 && f3)
{
	return [=] < typename T > (T && x) 
	{ 
		return f3
		(
			f1(std::forward < T > (x)), 
			
			f2(std::forward < T > (x))
		);
	};
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------

	std::erase_if
	(	
		vector, bind
		(
			[](auto x){ return x == 1; },

			[](auto x){ return x == 2; }, std::logical_or <> ()
		)
	);

//  -----------------------------------------------------------

	assert(vector == std::vector < int > ({ 3, 4, 5 }));
}