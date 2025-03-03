#include <cassert>
#include <functional>
#include <vector>

//////////////////////////////////////////////////////////

int main()
{
//	std::vector < int & > vector; // error

	std::vector < std::reference_wrapper < int > > vector;

	auto x = 1;

	vector.push_back(x);

	vector.back().get() = 2;
	
	assert(x == 2);
}