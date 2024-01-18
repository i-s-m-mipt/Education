#include <algorithm>
#include <cassert>
#include <deque>
#include <iterator>
#include <list>
#include <set>
#include <vector>

int main()
{
	std::vector < int > v({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

	std::deque  < int > d; // note: has push_front  member function
	std::list   < int > l; // note: has push_back   member function
	std::set    < int > s; // note: has only insert member function

	std::copy(std::cbegin(v), std::cend(v), std::front_inserter(d));
	std::copy(std::cbegin(v), std::cend(v), std:: back_inserter(l));
	std::copy(std::cbegin(v), std::cend(v), std::      inserter(s, std::begin(s)));

	assert(std::size(d) == std::size(v));
	assert(std::size(l) == std::size(v));
	assert(std::size(s) == std::size(v));

	return 0;
}